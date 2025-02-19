// This file implements the ICreateTypeInfo Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyICreateTypeInfo.h"
#include "PyComTypeObjects.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyICreateTypeInfo::PyICreateTypeInfo(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyICreateTypeInfo::~PyICreateTypeInfo() {}

/* static */ ICreateTypeInfo *PyICreateTypeInfo::GetI(PyObject *self)
{
    return (ICreateTypeInfo *)PyIUnknown::GetI(self);
}

// @pymethod |PyICreateTypeInfo|SetGuid|Description of SetGuid.
PyObject *PyICreateTypeInfo::SetGuid(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm <o PyIID>|guid||Description for guid
    PyObject *obguid;
    IID guid;
    if (!PyArg_ParseTuple(args, "O:SetGuid", &obguid))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsIID(obguid, &guid))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetGuid(guid);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetTypeFlags|Description of SetTypeFlags.
PyObject *PyICreateTypeInfo::SetTypeFlags(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|uTypeFlags||Description for uTypeFlags
    UINT uTypeFlags;
    if (!PyArg_ParseTuple(args, "i:SetTypeFlags", &uTypeFlags))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetTypeFlags(uTypeFlags);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetDocString|Description of SetDocString.
PyObject *PyICreateTypeInfo::SetDocString(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm <o unicode>|pStrDoc||Description for pStrDoc
    PyObject *obpStrDoc;
    LPOLESTR pStrDoc;
    if (!PyArg_ParseTuple(args, "O:SetDocString", &obpStrDoc))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsBstr(obpStrDoc, &pStrDoc))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetDocString(pStrDoc);
    PY_INTERFACE_POSTCALL;
    SysFreeString(pStrDoc);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetHelpContext|Description of SetHelpContext.
PyObject *PyICreateTypeInfo::SetHelpContext(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|dwHelpContext||Description for dwHelpContext
    DWORD dwHelpContext;
    if (!PyArg_ParseTuple(args, "l:SetHelpContext", &dwHelpContext))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetHelpContext(dwHelpContext);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetVersion|Description of SetVersion.
PyObject *PyICreateTypeInfo::SetVersion(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|wMajorVerNum||Description for wMajorVerNum
    // @pyparm int|wMinorVerNum||Description for wMinorVerNum
    WORD wMajorVerNum;
    WORD wMinorVerNum;
    if (!PyArg_ParseTuple(args, "ii:SetVersion", &wMajorVerNum, &wMinorVerNum))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetVersion(wMajorVerNum, wMinorVerNum);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|AddRefTypeInfo|Description of AddRefTypeInfo.
PyObject *PyICreateTypeInfo::AddRefTypeInfo(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm <o PyITypeInfo>|pTInfo||Description for pTInfo
    PyObject *obpTInfo;
    ITypeInfo *pTInfo;
    if (!PyArg_ParseTuple(args, "O:AddRefTypeInfo", &obpTInfo))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpTInfo, IID_ITypeInfo, (void **)&pTInfo, TRUE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    HREFTYPE hRefType;
    PY_INTERFACE_PRECALL;
    hr = pICTI->AddRefTypeInfo(pTInfo, &hRefType);
    if (pTInfo)
        pTInfo->Release();
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    return PyLong_FromLong(hRefType);
}

// @pymethod |PyICreateTypeInfo|AddFuncDesc|Description of AddFuncDesc.
PyObject *PyICreateTypeInfo::AddFuncDesc(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    FUNCDESC *pFuncDesc;
    PyObject *obpFuncDesc;
    UINT index;
    if (!PyArg_ParseTuple(args, "iO:AddFuncDesc", &index, &obpFuncDesc))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (bPythonIsHappy && !PyObject_AsFUNCDESC(obpFuncDesc, &pFuncDesc))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->AddFuncDesc(index, pFuncDesc);
    PY_INTERFACE_POSTCALL;

    PyObject_FreeFUNCDESC(pFuncDesc);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|AddImplType|Description of AddImplType.
PyObject *PyICreateTypeInfo::AddImplType(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm int|hRefType||A hRefType
    long hRefType;
    UINT index;
    if (!PyArg_ParseTuple(args, "il:AddImplType", &index, &hRefType))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->AddImplType(index, hRefType);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetImplTypeFlags|Description of SetImplTypeFlags.
PyObject *PyICreateTypeInfo::SetImplTypeFlags(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm int|implTypeFlags||Description for implTypeFlags
    UINT index;
    INT implTypeFlags;
    if (!PyArg_ParseTuple(args, "ii:SetImplTypeFlags", &index, &implTypeFlags))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetImplTypeFlags(index, implTypeFlags);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetAlignment|Description of SetAlignment.
PyObject *PyICreateTypeInfo::SetAlignment(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|cbAlignment||Description for cbAlignment
    WORD cbAlignment;
    if (!PyArg_ParseTuple(args, "i:SetAlignment", &cbAlignment))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetAlignment(cbAlignment);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetSchema|Description of SetSchema.
PyObject *PyICreateTypeInfo::SetSchema(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm <o unicode>|pStrSchema||Description for pStrSchema
    PyObject *obpStrSchema;
    LPOLESTR pStrSchema;
    if (!PyArg_ParseTuple(args, "O:SetSchema", &obpStrSchema))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsBstr(obpStrSchema, &pStrSchema))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetSchema(pStrSchema);
    PY_INTERFACE_POSTCALL;
    SysFreeString(pStrSchema);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|AddVarDesc|Description of AddVarDesc.
PyObject *PyICreateTypeInfo::AddVarDesc(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    VARDESC *pVarDesc;
    PyObject *obpVarDesc;
    UINT index;
    if (!PyArg_ParseTuple(args, "iO:AddVarDesc", &index, &obpVarDesc))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (bPythonIsHappy && !PyObject_AsVARDESC(obpVarDesc, &pVarDesc))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->AddVarDesc(index, pVarDesc);
    PY_INTERFACE_POSTCALL;

    PyObject_FreeVARDESC(pVarDesc);
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetFuncAndParamNames|Description of SetFuncAndParamNames.
PyObject *PyICreateTypeInfo::SetFuncAndParamNames(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Index of the item to set.
    // @pyparm (<o unicode>, ...)|rgszNames||A sequence of unicode or String objects.
    PyObject *obrgszNames;
    UINT index;
    if (!PyArg_ParseTuple(args, "iO:SetFuncAndParamNames", &index, &obrgszNames))
        return NULL;
    BOOL bPythonIsHappy = TRUE;

    // String and Unicode will pass the "is sequence" test, so we reject these!
    BSTR bstrTemp;
    if (PyWinObject_AsBstr(obrgszNames, &bstrTemp)) {
        PyWinObject_FreeBstr(bstrTemp);
        PyErr_SetString(PyExc_TypeError, "The names param must be a sequence of strings/unicodes");
        return NULL;
    }
    PyErr_Clear();  // clear the exception set by PyWinObject_AsBstr
    if (!PySequence_Check(obrgszNames)) {
        PyErr_SetString(PyExc_TypeError, "The names param must be a sequence of strings/unicodes");
        return NULL;
    }
    Py_ssize_t cNames = PySequence_Length(obrgszNames);
    PYWIN_CHECK_SSIZE_DWORD(cNames, NULL);

    OLECHAR **pNames = new OLECHAR *[cNames];
    memset(pNames, 0, sizeof(OLECHAR *) * cNames);
    Py_ssize_t i;
    for (i = 0; bPythonIsHappy && i < cNames; i++) {
        PyObject *item = PySequence_GetItem(obrgszNames, i);
        if (item == NULL)
            bPythonIsHappy = FALSE;
        else
            bPythonIsHappy = PyWinObject_AsBstr(item, pNames + i);
        Py_DECREF(item);
    }
    if (!bPythonIsHappy) {
        for (i = 0; i < cNames; i++) PyWinObject_FreeBstr(pNames[i]);
        delete pNames;
        return NULL;
    }
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetFuncAndParamNames(index, pNames, (UINT)cNames);
    PY_INTERFACE_POSTCALL;

    for (i = 0; i < cNames; i++) PyWinObject_FreeBstr(pNames[i]);
    delete pNames;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetVarName|Description of SetVarName.
PyObject *PyICreateTypeInfo::SetVarName(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm <o unicode>|szName||Description for szName
    PyObject *obszName;
    UINT index;
    LPOLESTR szName;
    if (!PyArg_ParseTuple(args, "iO:SetVarName", &index, &obszName))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsBstr(obszName, &szName))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetVarName(index, szName);
    PY_INTERFACE_POSTCALL;
    SysFreeString(szName);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetTypeDescAlias|Description of SetTypeDescAlias.
PyObject *PyICreateTypeInfo::SetTypeDescAlias(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    TYPEDESC *pTDescAlias;
    PyObject *obpTDescAlias;
    if (!PyArg_ParseTuple(args, "O:SetTypeDescAlias", &obpTDescAlias))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (bPythonIsHappy && !PyObject_AsTYPEDESC(obpTDescAlias, &pTDescAlias))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetTypeDescAlias(pTDescAlias);
    PY_INTERFACE_POSTCALL;

    PyObject_FreeTYPEDESC(pTDescAlias);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|DefineFuncAsDllEntry|Description of DefineFuncAsDllEntry.
PyObject *PyICreateTypeInfo::DefineFuncAsDllEntry(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm <o unicode>|szDllName||Description for szDllName
    // @pyparm <o unicode>|szProcName||Description for szProcName
    PyObject *obszDllName;
    PyObject *obszProcName;
    UINT index;
    LPOLESTR szDllName;
    LPOLESTR szProcName;
    if (!PyArg_ParseTuple(args, "iOO:DefineFuncAsDllEntry", &index, &obszDllName, &obszProcName))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsBstr(obszDllName, &szDllName))
        bPythonIsHappy = FALSE;
    if (!PyWinObject_AsBstr(obszProcName, &szProcName))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->DefineFuncAsDllEntry(index, szDllName, szProcName);
    PY_INTERFACE_POSTCALL;
    SysFreeString(szDllName);
    SysFreeString(szProcName);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetFuncDocString|Description of SetFuncDocString.
PyObject *PyICreateTypeInfo::SetFuncDocString(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm <o unicode>|szDocString||Description for szDocString
    PyObject *obszDocString;
    UINT index;
    LPOLESTR szDocString;
    if (!PyArg_ParseTuple(args, "iO:SetFuncDocString", &index, &obszDocString))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsBstr(obszDocString, &szDocString))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetFuncDocString(index, szDocString);
    PY_INTERFACE_POSTCALL;
    SysFreeString(szDocString);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetVarDocString|Description of SetVarDocString.
PyObject *PyICreateTypeInfo::SetVarDocString(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm <o unicode>|szDocString||Description for szDocString
    PyObject *obszDocString;
    UINT index;
    LPOLESTR szDocString;
    if (!PyArg_ParseTuple(args, "iO:SetVarDocString", &index, &obszDocString))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsBstr(obszDocString, &szDocString))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetVarDocString(index, szDocString);
    PY_INTERFACE_POSTCALL;
    SysFreeString(szDocString);

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetFuncHelpContext|Description of SetFuncHelpContext.
PyObject *PyICreateTypeInfo::SetFuncHelpContext(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm int|dwHelpContext||Description for dwHelpContext
    UINT index;
    DWORD dwHelpContext;
    if (!PyArg_ParseTuple(args, "il:SetFuncHelpContext", &index, &dwHelpContext))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetFuncHelpContext(index, dwHelpContext);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetVarHelpContext|Description of SetVarHelpContext.
PyObject *PyICreateTypeInfo::SetVarHelpContext(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm int|dwHelpContext||Description for dwHelpContext
    UINT index;
    DWORD dwHelpContext;
    if (!PyArg_ParseTuple(args, "il:SetVarHelpContext", &index, &dwHelpContext))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetVarHelpContext(index, dwHelpContext);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyICreateTypeInfo|SetMops|Description of SetMops.
PyObject *PyICreateTypeInfo::SetMops(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    // @pyparm int|index||Description for index
    // @pyparm <o unicode>|bstrMops||Description for bstrMops
    PyObject *obbstrMops;
    UINT index;
    BSTR bstrMops;
    if (!PyArg_ParseTuple(args, "iO:SetMops", &index, &obbstrMops))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsBstr(obbstrMops, &bstrMops))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetMops(index, bstrMops);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}
/*****
// @pymethod |PyICreateTypeInfo|SetTypeIdldesc|Description of SetTypeIdldesc.
PyObject *PyICreateTypeInfo::SetTypeIdldesc(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if ( pICTI == NULL )
        return NULL;
    // @pyparm <o PyIDLDESC>|pIdlDesc||Description for pIdlDesc
    PyObject *obpIdlDesc;
    IDLDESC * pIdlDesc;
    if ( !PyArg_ParseTuple(args, "O:SetTypeIdldesc", &obpIdlDesc) )
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpIdlDesc, IID_IDLDESC, (void **)&pIdlDesc, TRUE ))
         bPythonIsHappy = FALSE;
    if (!bPythonIsHappy) return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->SetTypeIdldesc( pIdlDesc );
    if (pIdlDesc) pIdlDesc->Release();
    PY_INTERFACE_POSTCALL;

    if ( FAILED(hr) )
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;

}
****/
// @pymethod |PyICreateTypeInfo|LayOut|Description of LayOut.
PyObject *PyICreateTypeInfo::LayOut(PyObject *self, PyObject *args)
{
    ICreateTypeInfo *pICTI = GetI(self);
    if (pICTI == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":LayOut"))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICTI->LayOut();
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICTI, IID_ICreateTypeInfo);
    Py_INCREF(Py_None);
    return Py_None;
}

// @object PyICreateTypeInfo|Description of the interface
static struct PyMethodDef PyICreateTypeInfo_methods[] = {
    {"SetGuid", PyICreateTypeInfo::SetGuid, 1},                // @pymeth SetGuid|Description of SetGuid
    {"SetTypeFlags", PyICreateTypeInfo::SetTypeFlags, 1},      // @pymeth SetTypeFlags|Description of SetTypeFlags
    {"SetDocString", PyICreateTypeInfo::SetDocString, 1},      // @pymeth SetDocString|Description of SetDocString
    {"SetHelpContext", PyICreateTypeInfo::SetHelpContext, 1},  // @pymeth SetHelpContext|Description of SetHelpContext
    {"SetVersion", PyICreateTypeInfo::SetVersion, 1},          // @pymeth SetVersion|Description of SetVersion
    {"AddRefTypeInfo", PyICreateTypeInfo::AddRefTypeInfo, 1},  // @pymeth AddRefTypeInfo|Description of AddRefTypeInfo
    {"AddFuncDesc", PyICreateTypeInfo::AddFuncDesc, 1},        // @pymeth AddFuncDesc|Description of AddFuncDesc
    {"AddImplType", PyICreateTypeInfo::AddImplType, 1},        // @pymeth AddImplType|Description of AddImplType
    {"SetImplTypeFlags", PyICreateTypeInfo::SetImplTypeFlags,
     1},                                                   // @pymeth SetImplTypeFlags|Description of SetImplTypeFlags
    {"SetAlignment", PyICreateTypeInfo::SetAlignment, 1},  // @pymeth SetAlignment|Description of SetAlignment
    {"SetSchema", PyICreateTypeInfo::SetSchema, 1},        // @pymeth SetSchema|Description of SetSchema
    {"AddVarDesc", PyICreateTypeInfo::AddVarDesc, 1},      // @pymeth AddVarDesc|Description of AddVarDesc
    {"SetFuncAndParamNames", PyICreateTypeInfo::SetFuncAndParamNames,
     1},  // @pymeth SetFuncAndParamNames|Description of SetFuncAndParamNames
    {"SetVarName", PyICreateTypeInfo::SetVarName, 1},  // @pymeth SetVarName|Description of SetVarName
    {"SetTypeDescAlias", PyICreateTypeInfo::SetTypeDescAlias,
     1},  // @pymeth SetTypeDescAlias|Description of SetTypeDescAlias
    {"DefineFuncAsDllEntry", PyICreateTypeInfo::DefineFuncAsDllEntry,
     1},  // @pymeth DefineFuncAsDllEntry|Description of DefineFuncAsDllEntry
    {"SetFuncDocString", PyICreateTypeInfo::SetFuncDocString,
     1},  // @pymeth SetFuncDocString|Description of SetFuncDocString
    {"SetVarDocString", PyICreateTypeInfo::SetVarDocString,
     1},  // @pymeth SetVarDocString|Description of SetVarDocString
    {"SetFuncHelpContext", PyICreateTypeInfo::SetFuncHelpContext,
     1},  // @pymeth SetFuncHelpContext|Description of SetFuncHelpContext
    {"SetVarHelpContext", PyICreateTypeInfo::SetVarHelpContext,
     1},                                         // @pymeth SetVarHelpContext|Description of SetVarHelpContext
    {"SetMops", PyICreateTypeInfo::SetMops, 1},  // @pymeth SetMops|Description of SetMops
    {"LayOut", PyICreateTypeInfo::LayOut, 1},    // @pymeth LayOut|Description of LayOut
    {NULL}};

PyComTypeObject PyICreateTypeInfo::type("PyICreateTypeInfo", &PyIUnknown::type, sizeof(PyICreateTypeInfo),
                                        PyICreateTypeInfo_methods, GET_PYCOM_CTOR(PyICreateTypeInfo));
