// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.5.0
//
// <auto-generated>
//
// Generated from file `MiddlewareTestbed.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

package MiddlewareTestbed;

public final class _ItemBDelD extends Ice._ObjectDelD implements _ItemBDel
{
    public int get_item_age(java.util.Map<String, String> __ctx, Ice.Instrumentation.InvocationObserver __observer)
        throws IceInternal.LocalExceptionWrapper
    {
        final Ice.Current __current = new Ice.Current();
        __initCurrent(__current, "get_item_age", Ice.OperationMode.Idempotent, __ctx);
        final Ice.IntHolder __result = new Ice.IntHolder();
        IceInternal.Direct __direct = null;
        try
        {
            __direct = new IceInternal.Direct(__current)
            {
                public Ice.DispatchStatus run(Ice.Object __obj)
                {
                    ItemB __servant = null;
                    if(__obj == null || __obj instanceof ItemB)
                    {
                        __servant = (ItemB)__obj;
                    }
                    else
                    {
                        throw new Ice.OperationNotExistException(__current.id, __current.facet, __current.operation);
                    }
                    __result.value = __servant.get_item_age(__current);
                    return Ice.DispatchStatus.DispatchOK;
                }
            };
            try
            {
                Ice.DispatchStatus __status = __direct.getServant().__collocDispatch(__direct);
                if(__status == Ice.DispatchStatus.DispatchUserException)
                {
                    __direct.throwUserException();
                }
                assert __status == Ice.DispatchStatus.DispatchOK;
                return __result.value;
            }
            finally
            {
                __direct.destroy();
            }
        }
        catch(Ice.SystemException __ex)
        {
            throw __ex;
        }
        catch(java.lang.Throwable __ex)
        {
            IceInternal.LocalExceptionWrapper.throwWrapper(__ex);
        }
        return __result.value;
    }

    public String name(java.util.Map<String, String> __ctx, Ice.Instrumentation.InvocationObserver __observer)
        throws IceInternal.LocalExceptionWrapper
    {
        final Ice.Current __current = new Ice.Current();
        __initCurrent(__current, "name", Ice.OperationMode.Idempotent, __ctx);
        final Ice.StringHolder __result = new Ice.StringHolder();
        IceInternal.Direct __direct = null;
        try
        {
            __direct = new IceInternal.Direct(__current)
            {
                public Ice.DispatchStatus run(Ice.Object __obj)
                {
                    ItemB __servant = null;
                    if(__obj == null || __obj instanceof ItemB)
                    {
                        __servant = (ItemB)__obj;
                    }
                    else
                    {
                        throw new Ice.OperationNotExistException(__current.id, __current.facet, __current.operation);
                    }
                    __result.value = __servant.name(__current);
                    return Ice.DispatchStatus.DispatchOK;
                }
            };
            try
            {
                Ice.DispatchStatus __status = __direct.getServant().__collocDispatch(__direct);
                if(__status == Ice.DispatchStatus.DispatchUserException)
                {
                    __direct.throwUserException();
                }
                assert __status == Ice.DispatchStatus.DispatchOK;
                return __result.value;
            }
            finally
            {
                __direct.destroy();
            }
        }
        catch(Ice.SystemException __ex)
        {
            throw __ex;
        }
        catch(java.lang.Throwable __ex)
        {
            IceInternal.LocalExceptionWrapper.throwWrapper(__ex);
        }
        return __result.value;
    }

    public float actionB(final String a, java.util.Map<String, String> __ctx, Ice.Instrumentation.InvocationObserver __observer)
        throws IceInternal.LocalExceptionWrapper
    {
        final Ice.Current __current = new Ice.Current();
        __initCurrent(__current, "actionB", Ice.OperationMode.Normal, __ctx);
        final Ice.FloatHolder __result = new Ice.FloatHolder();
        IceInternal.Direct __direct = null;
        try
        {
            __direct = new IceInternal.Direct(__current)
            {
                public Ice.DispatchStatus run(Ice.Object __obj)
                {
                    ItemB __servant = null;
                    if(__obj == null || __obj instanceof ItemB)
                    {
                        __servant = (ItemB)__obj;
                    }
                    else
                    {
                        throw new Ice.OperationNotExistException(__current.id, __current.facet, __current.operation);
                    }
                    __result.value = __servant.actionB(a, __current);
                    return Ice.DispatchStatus.DispatchOK;
                }
            };
            try
            {
                Ice.DispatchStatus __status = __direct.getServant().__collocDispatch(__direct);
                if(__status == Ice.DispatchStatus.DispatchUserException)
                {
                    __direct.throwUserException();
                }
                assert __status == Ice.DispatchStatus.DispatchOK;
                return __result.value;
            }
            finally
            {
                __direct.destroy();
            }
        }
        catch(Ice.SystemException __ex)
        {
            throw __ex;
        }
        catch(java.lang.Throwable __ex)
        {
            IceInternal.LocalExceptionWrapper.throwWrapper(__ex);
        }
        return __result.value;
    }
}
