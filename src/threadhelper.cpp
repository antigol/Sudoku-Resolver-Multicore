#include "threadhelper.h"

#define DBLINE qDebug("debug, line %d", __LINE__);

ThreadHelper::ThreadHelper()
    : _status(0)
{
    _cpu = cpuThreads();
}

void ThreadHelper::start(SudokuGame jeu)
{
    reset();
    _jeux = decomposerEn(jeu, _cpu);
    cout << QString(trUtf8("la liste de threads contient %1 threads.")).arg(_jeux.size()) << endl;

    while(_tlist.size() < _jeux.size())
    {
        int i(_tlist.size());
        SudokuThread* tr = new SudokuThread(this, _jeux[i]);
        connect(tr, SIGNAL(finished()), this, SLOT(endThread()));
        _tlist.append(tr);
    }
    for(int i(0); i<_cpu && i<_tlist.size(); ++i)
        _tlist[i]->start();
    _status = 1;

    if(_jeux.size() == 0) endThread();
}

void ThreadHelper::stop()
{
    _status |= 2;

    for(int i(0); i<_tlist.size(); ++i)
        _tlist[i]->stop();
    for(int i(0); i<_tlist.size(); ++i)
        _tlist[i]->wait();
}

void ThreadHelper::reset()
{
    for(int i(0); i<_tlist.size(); ++i)
        delete _tlist[i];
    _tlist.clear();
    _jeux.clear();
    _status = 0;
}

// _status  veutstop - run
void ThreadHelper::endThread()
{
    for(int i(0); i<_tlist.size(); ++i)
    {
        if(!(_status&2) && !_tlist[i]->dejaRun())
        {
            _tlist[i]->start();
            return;
        }
    }

    if(_status&1 && !nthr())
    {
        _status &= ~1;
        emit finished();
    }
}

ulong ThreadHelper::nbrall() const
{
    ulong nbr(0);
    for(int i(0); i<_tlist.size(); ++i)
        nbr += _tlist[i]->nbrSolutions();
    return nbr;
}

ulong ThreadHelper::nbrsave() const
{
    ulong nbr(0);
    for(int i(0); i<_tlist.size(); ++i)
        nbr += _tlist[i]->getSolutions().size();
    return nbr;
}

SudokuData ThreadHelper::solAt(ulong i) const
{
    for(int k(0); k<_tlist.size(); ++k)
    {
        const BigList<SudokuData> &data(_tlist[k]->getSolutions());
        if(i < data.size()) return data[i];
        i -= data.size();
    }
    return SudokuData();
}

int ThreadHelper::nthr() const
{
    int nbr(0);
    for(int i(0); i<_tlist.size(); ++i)
        if(_tlist[i]->isRunning()) nbr++;
    return nbr;
}

QList<SudokuGame> ThreadHelper::decomposer(SudokuGame jeu)
{
    QList<SudokuGame> list;
    int maximum(0);
    int id(0);
    while (jeu.recherche()) ; // ajout
    for (int i(0); i<81; ++i) {
        if (jeu[i].digitAmount() != 1 && jeu[i].digitAmount() > maximum) {
            maximum = jeu[i].digitAmount();
            id = i;
        }
    }

    SudokuGame save(jeu);

    for (int chiffre=UN; chiffre<TOUS; chiffre<<=1) {
        if(jeu[id].dataList() & chiffre) {
            jeu[id].setValue(chiffre);

            while (jeu.recherche()) ;

            if (jeu.verification()) {
                list.append(jeu);
            }
            jeu = save;
        }
    }

    return list;
}

QList<SudokuGame> ThreadHelper::decomposerEn(SudokuGame jeu, int min)
{
    QList<SudokuGame> list(decomposer(jeu));
    if (list.size() <= 1) return list;

    while (list.size() < min) {
        QList<QList<SudokuGame> > lists;
        for(int i(0); i<list.size(); ++i)
            lists.append(decomposer(list[i]));

        int need(min - list.size() - 1);
        int delta(INT_MAX);
        int id(-1);

        int maximum(0);
        int idmax(0);
        for(int i(0); i<lists.size(); ++i)
        {
            int surplus( lists[i].size() - need);
            if(surplus > 0 && surplus < delta)
            {
                delta = surplus;
                id = i;
            }

            if(lists[i].size() > maximum)
            {
                maximum = lists[i].size();
                idmax = i;
            }
        }

        if(id == -1)
        {
            list.removeAt(idmax);
            list.append(lists[idmax]);
        }
        else
        {
            list.removeAt(id);
            list.append(lists[id]);
        }
        if(maximum == 1) break;
    }

    return list;
}

#include <qglobal.h>
#if defined(Q_OS_WIN)
#  include <windows.h>
#elif defined(Q_OS_LINUX)
#  include <unistd.h>
#elif defined(Q_OS_MAC)
#  include <mach/mach.h>
#  include <mach/machine.h>
#elif defined(Q_OS_OS2)
#define INCL_DOSMISC
#include <os2.h>

#ifndef QSV_NUMPROCESSORS
/*The QSV_NUMPROCESSORS is only defined in the SMP toolkit,
 *and since the SMP toolkit is always at least 6 months behind
 *the normal toolkit you will probably not want use it.
 */
#define QSV_NUMPROCESSORS 26
#endif
#endif

int ThreadHelper::cpuThreads() const
{
    int cpu(1);
#if defined(Q_OS_WIN)
    SYSTEM_INFO si;
    memset( &si, 0, sizeof(si));
    GetSystemInfo( &si);
    cpu = si.dwNumberOfProcessors;
#elif defined(Q_OS_LINUX)
    cpu = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(Q_OS_MAC)
    kern_return_t kr;
    struct host_basic_info hostinfo;
    unsigned int count;

    count = HOST_BASIC_INFO_COUNT;
    kr = host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)&hostinfo, &count);
    if(kr == KERN_SUCCESS)
    {
        cpu = hostinfo.avail_cpus;
        // totalMemory = hostinfo.memory_size; //in bytes
    }
#elif defined(Q_OS_OS2)
    ULONG CPUs;
    APIRET rc;
    CPUs = 0;
    rc = DosQuerySysInfo(QSV_NUMPROCESSORS,
                         QSV_NUMPROCESSORS,
                         &CPUs,
                         sizeof(CPUs));
    /*We have to guard against running under a non-SMP OS/2
   *that does not support index 26, and that index 26 (as
   *far as I remember) has previously been used for
   *something else
   */

    if(rc!=0 || CPUs<1 || CPUs>64)
        CPUs = 1;
    cpu = CPUs;
#endif
    if(cpu < 1) cpu = 1;

    return cpu;
}

QTextStream cout(stdout, QIODevice::WriteOnly);
