#ifndef H_BIGLIST
#define H_BIGLIST

#include <stdlib.h>
#include <string.h>

template <class T> class BigList
{
public:
  BigList();
  BigList(const BigList &b);
  ~BigList();

  unsigned long size() const;
  bool append(const T &item);
  void clear();

  T &operator[](unsigned long i);
  const T &operator[](unsigned long i) const;

  bool resize(unsigned long s);
private:
  unsigned long _s;
  unsigned long _ss;
  T *_t;
};


template <class T>
    BigList<T>::BigList()
      : _s(0), _ss(1), _t(NULL)
{
}

template <class T>
    BigList<T>::BigList(const BigList &b)
      : _s(b.size()), _ss(b._ss)
{
  _t = (T*)malloc(_ss * sizeof(T));
  memcpy(_t, b._t, _s);
}

template <class T>
    BigList<T>::~BigList()
{
  free(_t);
}

template <class T>
    unsigned long BigList<T>::size() const
{
  return _s;
}

template <class T>
    bool BigList<T>::append(const T &item)
{
  if(!_ss) return false;

  if(_t) {
    if(_s == _ss) {
      _ss *= 2;
//      T *tmp = (T*)realloc(_t, _ss * sizeof(T));
//      if( !tmp ) {
//        _ss = 0;
//        return false;
//      }
//      _t = tmp;
      T *tmp = (T*)malloc(_ss * sizeof(T));
      if (!tmp) {
        _ss = 0;
        return false;
      }
      memcpy(tmp, _t, _s * sizeof(T));
      free(_t);
      _t = tmp;
      //qDebug("realloc with %f Mio.", _ss * sizeof(T) / 1024.0);
    }
  } else {
    _t = (T*)malloc(sizeof(T));
  }

  _t[_s] = item;
  ++_s;
  return true;
}

template <class T>
    void BigList<T>::clear()
{
  free(_t);
  _t = NULL;
  _s = 0;
  _ss = 1;
}

template <class T>
    T &BigList<T>::operator[](unsigned long i)
{
  return _t[i];
}

template <class T>
    const T &BigList<T>::operator[](unsigned long i) const
{
  return _t[i];
}

template <class T>
    bool BigList<T>::resize(unsigned long s)
{
  if(!s) return false;
  if(s<_s) return false;

  T *tmp = (T*)realloc(_t, s * sizeof(T));
  if(!tmp) return false;

  _t = tmp;
  _ss = s;
  return true;
}

#endif
