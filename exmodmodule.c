#include<Python.h>
#include <stdio.h>
#include<time.h>
static PyObject *exmodError;

int nsleep(long miliseconds)
{
   struct timespec req, rem;
   //printf("This is the passed milliseconds %ld",miliseconds);
   if(miliseconds > 999)
   {   
        req.tv_sec = (int)(miliseconds / 1000);                            /* Must be Non-Negative */
        req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
   }   
   else
   {   
        req.tv_sec = 0;                         /* Must be Non-Negative */
        req.tv_nsec = miliseconds * 1000000;    /* Must be in range of 0 to 999999999 */
   }   

   return nanosleep(&req , &rem);
}



static PyObject* exmod_say_hello(PyObject *self, PyObject *args){
  const char* msg;
  int sts=0;

  if(!PyArg_ParseTuple(args, "s", &msg)){
    return NULL;
  }

  if(strcmp(msg,"this_is_an_error") == 0){
    PyErr_SetString(exmodError, "This is a test exception error after typing an expectedinvalid respose");
    return NULL;
  }
  else{
    printf("This is C world\n Your message is %s\n",msg);
    sts=21;
  }
  return Py_BuildValue("i",sts);
}

static PyObject* exmod_add(PyObject* self, PyObject *args){
  double a;
  double sts=0;
  int k;
  //printf("entered the function");
  if(!PyArg_ParseTuple(args, "d", &a)){
    return NULL;
  }
  k=(int)a;
  int ret = nsleep(k);
  //printf("sleep result %d\n",ret);
  //printf("This is C world \n Addition of %d %f",k,a);
  return Py_BuildValue("d",sts);
}

static PyMethodDef exmod_methods[]={
  {"say_hello", exmod_say_hello, METH_VARARGS, "Say hello from C and print message"},
  {"add", exmod_add, METH_VARARGS, "ADD two number in C"},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initexmod(void){
  PyObject *m;
  m= Py_InitModule("exmod",exmod_methods);
  if(m==NULL) return;
  exmodError = PyErr_NewException("exmod.error",NULL,NULL);
  Py_INCREF(exmodError);

  PyModule_AddObject(m, "eroor",exmodError);
}
