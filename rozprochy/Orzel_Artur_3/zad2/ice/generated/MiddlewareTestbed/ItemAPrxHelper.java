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

public final class ItemAPrxHelper extends Ice.ObjectPrxHelperBase implements ItemAPrx
{
    private static final String __get_item_age_name = "get_item_age";

    public int get_item_age()
    {
        return get_item_age(null, false);
    }

    public int get_item_age(java.util.Map<String, String> __ctx)
    {
        return get_item_age(__ctx, true);
    }

    private int get_item_age(java.util.Map<String, String> __ctx, boolean __explicitCtx)
    {
        if(__explicitCtx && __ctx == null)
        {
            __ctx = _emptyContext;
        }
        final Ice.Instrumentation.InvocationObserver __observer = IceInternal.ObserverHelper.get(this, "get_item_age", __ctx);
        int __cnt = 0;
        try
        {
            while(true)
            {
                Ice._ObjectDel __delBase = null;
                try
                {
                    __checkTwowayOnly("get_item_age");
                    __delBase = __getDelegate(false);
                    _ItemADel __del = (_ItemADel)__delBase;
                    return __del.get_item_age(__ctx, __observer);
                }
                catch(IceInternal.LocalExceptionWrapper __ex)
                {
                    __cnt = __handleExceptionWrapperRelaxed(__delBase, __ex, null, __cnt, __observer);
                }
                catch(Ice.LocalException __ex)
                {
                    __cnt = __handleException(__delBase, __ex, null, __cnt, __observer);
                }
            }
        }
        finally
        {
            if(__observer != null)
            {
                __observer.detach();
            }
        }
    }

    public Ice.AsyncResult begin_get_item_age()
    {
        return begin_get_item_age(null, false, null);
    }

    public Ice.AsyncResult begin_get_item_age(java.util.Map<String, String> __ctx)
    {
        return begin_get_item_age(__ctx, true, null);
    }

    public Ice.AsyncResult begin_get_item_age(Ice.Callback __cb)
    {
        return begin_get_item_age(null, false, __cb);
    }

    public Ice.AsyncResult begin_get_item_age(java.util.Map<String, String> __ctx, Ice.Callback __cb)
    {
        return begin_get_item_age(__ctx, true, __cb);
    }

    public Ice.AsyncResult begin_get_item_age(Callback_Item_get_item_age __cb)
    {
        return begin_get_item_age(null, false, __cb);
    }

    public Ice.AsyncResult begin_get_item_age(java.util.Map<String, String> __ctx, Callback_Item_get_item_age __cb)
    {
        return begin_get_item_age(__ctx, true, __cb);
    }

    private Ice.AsyncResult begin_get_item_age(java.util.Map<String, String> __ctx, boolean __explicitCtx, IceInternal.CallbackBase __cb)
    {
        __checkAsyncTwowayOnly(__get_item_age_name);
        IceInternal.OutgoingAsync __result = new IceInternal.OutgoingAsync(this, __get_item_age_name, __cb);
        try
        {
            __result.__prepare(__get_item_age_name, Ice.OperationMode.Idempotent, __ctx, __explicitCtx);
            __result.__writeEmptyParams();
            __result.__send(true);
        }
        catch(Ice.LocalException __ex)
        {
            __result.__exceptionAsync(__ex);
        }
        return __result;
    }

    public int end_get_item_age(Ice.AsyncResult __result)
    {
        Ice.AsyncResult.__check(__result, this, __get_item_age_name);
        boolean __ok = __result.__wait();
        try
        {
            if(!__ok)
            {
                try
                {
                    __result.__throwUserException();
                }
                catch(Ice.UserException __ex)
                {
                    throw new Ice.UnknownUserException(__ex.ice_name(), __ex);
                }
            }
            IceInternal.BasicStream __is = __result.__startReadParams();
            int __ret;
            __ret = __is.readInt();
            __result.__endReadParams();
            return __ret;
        }
        catch(Ice.LocalException ex)
        {
            Ice.Instrumentation.InvocationObserver __obsv = __result.__getObserver();
            if(__obsv != null)
            {
                __obsv.failed(ex.ice_name());
            }
            throw ex;
        }
    }

    private static final String __name_name = "name";

    public String name()
    {
        return name(null, false);
    }

    public String name(java.util.Map<String, String> __ctx)
    {
        return name(__ctx, true);
    }

    private String name(java.util.Map<String, String> __ctx, boolean __explicitCtx)
    {
        if(__explicitCtx && __ctx == null)
        {
            __ctx = _emptyContext;
        }
        final Ice.Instrumentation.InvocationObserver __observer = IceInternal.ObserverHelper.get(this, "name", __ctx);
        int __cnt = 0;
        try
        {
            while(true)
            {
                Ice._ObjectDel __delBase = null;
                try
                {
                    __checkTwowayOnly("name");
                    __delBase = __getDelegate(false);
                    _ItemADel __del = (_ItemADel)__delBase;
                    return __del.name(__ctx, __observer);
                }
                catch(IceInternal.LocalExceptionWrapper __ex)
                {
                    __cnt = __handleExceptionWrapperRelaxed(__delBase, __ex, null, __cnt, __observer);
                }
                catch(Ice.LocalException __ex)
                {
                    __cnt = __handleException(__delBase, __ex, null, __cnt, __observer);
                }
            }
        }
        finally
        {
            if(__observer != null)
            {
                __observer.detach();
            }
        }
    }

    public Ice.AsyncResult begin_name()
    {
        return begin_name(null, false, null);
    }

    public Ice.AsyncResult begin_name(java.util.Map<String, String> __ctx)
    {
        return begin_name(__ctx, true, null);
    }

    public Ice.AsyncResult begin_name(Ice.Callback __cb)
    {
        return begin_name(null, false, __cb);
    }

    public Ice.AsyncResult begin_name(java.util.Map<String, String> __ctx, Ice.Callback __cb)
    {
        return begin_name(__ctx, true, __cb);
    }

    public Ice.AsyncResult begin_name(Callback_Item_name __cb)
    {
        return begin_name(null, false, __cb);
    }

    public Ice.AsyncResult begin_name(java.util.Map<String, String> __ctx, Callback_Item_name __cb)
    {
        return begin_name(__ctx, true, __cb);
    }

    private Ice.AsyncResult begin_name(java.util.Map<String, String> __ctx, boolean __explicitCtx, IceInternal.CallbackBase __cb)
    {
        __checkAsyncTwowayOnly(__name_name);
        IceInternal.OutgoingAsync __result = new IceInternal.OutgoingAsync(this, __name_name, __cb);
        try
        {
            __result.__prepare(__name_name, Ice.OperationMode.Idempotent, __ctx, __explicitCtx);
            __result.__writeEmptyParams();
            __result.__send(true);
        }
        catch(Ice.LocalException __ex)
        {
            __result.__exceptionAsync(__ex);
        }
        return __result;
    }

    public String end_name(Ice.AsyncResult __result)
    {
        Ice.AsyncResult.__check(__result, this, __name_name);
        boolean __ok = __result.__wait();
        try
        {
            if(!__ok)
            {
                try
                {
                    __result.__throwUserException();
                }
                catch(Ice.UserException __ex)
                {
                    throw new Ice.UnknownUserException(__ex.ice_name(), __ex);
                }
            }
            IceInternal.BasicStream __is = __result.__startReadParams();
            String __ret;
            __ret = __is.readString();
            __result.__endReadParams();
            return __ret;
        }
        catch(Ice.LocalException ex)
        {
            Ice.Instrumentation.InvocationObserver __obsv = __result.__getObserver();
            if(__obsv != null)
            {
                __obsv.failed(ex.ice_name());
            }
            throw ex;
        }
    }

    private static final String __actionA_name = "actionA";

    public void actionA(float a, Ice.IntHolder b)
    {
        actionA(a, b, null, false);
    }

    public void actionA(float a, Ice.IntHolder b, java.util.Map<String, String> __ctx)
    {
        actionA(a, b, __ctx, true);
    }

    private void actionA(float a, Ice.IntHolder b, java.util.Map<String, String> __ctx, boolean __explicitCtx)
    {
        if(__explicitCtx && __ctx == null)
        {
            __ctx = _emptyContext;
        }
        final Ice.Instrumentation.InvocationObserver __observer = IceInternal.ObserverHelper.get(this, "actionA", __ctx);
        int __cnt = 0;
        try
        {
            while(true)
            {
                Ice._ObjectDel __delBase = null;
                try
                {
                    __checkTwowayOnly("actionA");
                    __delBase = __getDelegate(false);
                    _ItemADel __del = (_ItemADel)__delBase;
                    __del.actionA(a, b, __ctx, __observer);
                    return;
                }
                catch(IceInternal.LocalExceptionWrapper __ex)
                {
                    __handleExceptionWrapper(__delBase, __ex, __observer);
                }
                catch(Ice.LocalException __ex)
                {
                    __cnt = __handleException(__delBase, __ex, null, __cnt, __observer);
                }
            }
        }
        finally
        {
            if(__observer != null)
            {
                __observer.detach();
            }
        }
    }

    public Ice.AsyncResult begin_actionA(float a)
    {
        return begin_actionA(a, null, false, null);
    }

    public Ice.AsyncResult begin_actionA(float a, java.util.Map<String, String> __ctx)
    {
        return begin_actionA(a, __ctx, true, null);
    }

    public Ice.AsyncResult begin_actionA(float a, Ice.Callback __cb)
    {
        return begin_actionA(a, null, false, __cb);
    }

    public Ice.AsyncResult begin_actionA(float a, java.util.Map<String, String> __ctx, Ice.Callback __cb)
    {
        return begin_actionA(a, __ctx, true, __cb);
    }

    public Ice.AsyncResult begin_actionA(float a, Callback_ItemA_actionA __cb)
    {
        return begin_actionA(a, null, false, __cb);
    }

    public Ice.AsyncResult begin_actionA(float a, java.util.Map<String, String> __ctx, Callback_ItemA_actionA __cb)
    {
        return begin_actionA(a, __ctx, true, __cb);
    }

    private Ice.AsyncResult begin_actionA(float a, java.util.Map<String, String> __ctx, boolean __explicitCtx, IceInternal.CallbackBase __cb)
    {
        __checkAsyncTwowayOnly(__actionA_name);
        IceInternal.OutgoingAsync __result = new IceInternal.OutgoingAsync(this, __actionA_name, __cb);
        try
        {
            __result.__prepare(__actionA_name, Ice.OperationMode.Normal, __ctx, __explicitCtx);
            IceInternal.BasicStream __os = __result.__startWriteParams(Ice.FormatType.DefaultFormat);
            __os.writeFloat(a);
            __result.__endWriteParams();
            __result.__send(true);
        }
        catch(Ice.LocalException __ex)
        {
            __result.__exceptionAsync(__ex);
        }
        return __result;
    }

    public void end_actionA(Ice.IntHolder b, Ice.AsyncResult __result)
    {
        Ice.AsyncResult.__check(__result, this, __actionA_name);
        boolean __ok = __result.__wait();
        try
        {
            if(!__ok)
            {
                try
                {
                    __result.__throwUserException();
                }
                catch(Ice.UserException __ex)
                {
                    throw new Ice.UnknownUserException(__ex.ice_name(), __ex);
                }
            }
            IceInternal.BasicStream __is = __result.__startReadParams();
            b.value = __is.readInt();
            __result.__endReadParams();
        }
        catch(Ice.LocalException ex)
        {
            Ice.Instrumentation.InvocationObserver __obsv = __result.__getObserver();
            if(__obsv != null)
            {
                __obsv.failed(ex.ice_name());
            }
            throw ex;
        }
    }

    public static ItemAPrx checkedCast(Ice.ObjectPrx __obj)
    {
        ItemAPrx __d = null;
        if(__obj != null)
        {
            if(__obj instanceof ItemAPrx)
            {
                __d = (ItemAPrx)__obj;
            }
            else
            {
                if(__obj.ice_isA(ice_staticId()))
                {
                    ItemAPrxHelper __h = new ItemAPrxHelper();
                    __h.__copyFrom(__obj);
                    __d = __h;
                }
            }
        }
        return __d;
    }

    public static ItemAPrx checkedCast(Ice.ObjectPrx __obj, java.util.Map<String, String> __ctx)
    {
        ItemAPrx __d = null;
        if(__obj != null)
        {
            if(__obj instanceof ItemAPrx)
            {
                __d = (ItemAPrx)__obj;
            }
            else
            {
                if(__obj.ice_isA(ice_staticId(), __ctx))
                {
                    ItemAPrxHelper __h = new ItemAPrxHelper();
                    __h.__copyFrom(__obj);
                    __d = __h;
                }
            }
        }
        return __d;
    }

    public static ItemAPrx checkedCast(Ice.ObjectPrx __obj, String __facet)
    {
        ItemAPrx __d = null;
        if(__obj != null)
        {
            Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
            try
            {
                if(__bb.ice_isA(ice_staticId()))
                {
                    ItemAPrxHelper __h = new ItemAPrxHelper();
                    __h.__copyFrom(__bb);
                    __d = __h;
                }
            }
            catch(Ice.FacetNotExistException ex)
            {
            }
        }
        return __d;
    }

    public static ItemAPrx checkedCast(Ice.ObjectPrx __obj, String __facet, java.util.Map<String, String> __ctx)
    {
        ItemAPrx __d = null;
        if(__obj != null)
        {
            Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
            try
            {
                if(__bb.ice_isA(ice_staticId(), __ctx))
                {
                    ItemAPrxHelper __h = new ItemAPrxHelper();
                    __h.__copyFrom(__bb);
                    __d = __h;
                }
            }
            catch(Ice.FacetNotExistException ex)
            {
            }
        }
        return __d;
    }

    public static ItemAPrx uncheckedCast(Ice.ObjectPrx __obj)
    {
        ItemAPrx __d = null;
        if(__obj != null)
        {
            if(__obj instanceof ItemAPrx)
            {
                __d = (ItemAPrx)__obj;
            }
            else
            {
                ItemAPrxHelper __h = new ItemAPrxHelper();
                __h.__copyFrom(__obj);
                __d = __h;
            }
        }
        return __d;
    }

    public static ItemAPrx uncheckedCast(Ice.ObjectPrx __obj, String __facet)
    {
        ItemAPrx __d = null;
        if(__obj != null)
        {
            Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
            ItemAPrxHelper __h = new ItemAPrxHelper();
            __h.__copyFrom(__bb);
            __d = __h;
        }
        return __d;
    }

    public static final String[] __ids =
    {
        "::Ice::Object",
        "::MiddlewareTestbed::Item",
        "::MiddlewareTestbed::ItemA"
    };

    public static String ice_staticId()
    {
        return __ids[2];
    }

    protected Ice._ObjectDelM __createDelegateM()
    {
        return new _ItemADelM();
    }

    protected Ice._ObjectDelD __createDelegateD()
    {
        return new _ItemADelD();
    }

    public static void __write(IceInternal.BasicStream __os, ItemAPrx v)
    {
        __os.writeProxy(v);
    }

    public static ItemAPrx __read(IceInternal.BasicStream __is)
    {
        Ice.ObjectPrx proxy = __is.readProxy();
        if(proxy != null)
        {
            ItemAPrxHelper result = new ItemAPrxHelper();
            result.__copyFrom(proxy);
            return result;
        }
        return null;
    }

    public static final long serialVersionUID = 0L;
}
