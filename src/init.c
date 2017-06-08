#include <stdlib.h>
#include <R_ext/Rdynload.h>

/* .C calls */
extern void doproj(void *, void *, void *, void *, void *);
extern void setproj(void *, void *, void *, void *, void *);

static const R_CMethodDef CEntries[] = {
    {"doproj",  (DL_FUNC) &doproj,  5},
    {"setproj", (DL_FUNC) &setproj, 5},
    {NULL, NULL, 0}
};

void R_init_mapproj(DllInfo *dll)
{
    R_registerRoutines(dll, CEntries, NULL, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    R_forceSymbols(dll, TRUE);
}

