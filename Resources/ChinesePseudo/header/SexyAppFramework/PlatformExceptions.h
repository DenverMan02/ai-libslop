#ifndef PLATFORMEXCEPTIONS_H_INCLUDED
#define PLATFORMEXCEPTIONS_H_INCLUDED

#ifndef SUPPORT_EXCEPTIONS

//gnuc already does this, maybe others
#ifndef __GNUC__
#define try
#define throw(x) 
//((void)0)
#define catch(x) if (0)
#define catchall() if (0)
#endif

#endif


#endif