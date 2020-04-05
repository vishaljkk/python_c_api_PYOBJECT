
#include <stdio.h>
#include<Python.h>
#include<time.h>
static PyObject *exmodError;

int nsleep(long miliseconds)
{
   struct timespec req, rem;

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
  double a,b;
  double sts=0;
  printf("entered the function");
  if(!PyArg_ParseTuple(args, "dd", &a, &b)){
    return NULL;
  }

  sts= a+b;
  printf("This is C world \n Addition of %f + %f = %f",a,b,sts);
  return Py_BuildValue("d",sts);
}



static PyObject* exmod_nano(PyObject* self, PyObject *args){
  int a;
  double sts=0;
  printf("entered the function");
  if(!PyArg_ParseTuple(args, "i", &a)){
    return NULL;
  }
  printf("This passed int is %i",a);
  int ret = nsleep(10);
  printf("sleep result %d\n",ret);
  return Py_BuildValue("i",sts);
}

static PyMethodDef exmod_methods[]={
  {"say_hello", exmod_say_hello, METH_VARARGS, "Say hello from C and print message"},
  {"add", exmod_add, METH_VARARGS, "ADD two number in C"},
  {"ns", exmod_nano, METH_VARARGS, "Pass the time in nanosecond to sleep"},
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
