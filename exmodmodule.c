#include<Python.h>

static PyObject *exmodError;

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
