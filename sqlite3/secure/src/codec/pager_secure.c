#include "pager.c"

#ifndef SQLITE_OMIT_DISKIO

#ifdef SQLITE_HAS_CODEC
/*
** Get the codec argument for this pager
*/
void *sqlite3pager_get_codecarg(
  Pager *pPager
){
  return (pPager->xCodec) ? pPager->pCodecArg : NULL;
}
#endif

#endif

