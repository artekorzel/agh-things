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

public final class AFactoryPrxHelper extends Ice.ObjectPrxHelperBase implements AFactoryPrx
{
    private static final String __create_item_name = "create_item";

    public ItemPrx create_item(String name, String type)
        throws ItemAlreadyExists
    {
        return create_item(name, type, null, false);
    }

    public ItemPrx create_item(String name, String type, java.util.Map<String, String> __ctx)
        throws ItemAlreadyExists
    {
        return create_item(name, type, __ctx, true);
    }

    private ItemPrx create_item(String name, String type, java.util.Map<String, String> __ctx, boolean __explicitCtx)
        throws ItemAlreadyExists
    {
        if(__explicitCtx && __ctx == null)
        {
            __ctx = _emptyContext;
        }
        final Ice.Instrumentation.InvocationObserver __observer = IceInternal.ObserverHelper.get(this, "create_item", __ctx);
        int __cnt = 0;
        try
        {
            while(true)
            {
                Ice._ObjectDel __delBase = null;
                try
                {
                    __checkTwowayOnly("create_item");
                    __delBase = __getDelegate(false);
                    _AFactoryDel __del = (_AFactoryDel)__delBase;
                    return __del.create_item(name, type, __ctx, __observer);
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

    public Ice.AsyncResult begin_create_item(String name, String type)
    {
        return begin_create_item(name, type, null, false, null);
    }

    public Ice.AsyncResult begin_create_item(String name, String type, java.util.Map<String, String> __ctx)
    {
        return begin_create_item(name, type, __ctx, true, null);
    }

    public Ice.AsyncResult begin_create_item(String name, String type, Ice.Callback __cb)
    {
        return begin_create_item(name, type, null, false, __cb);
    }

    public Ice.AsyncResult begin_create_item(String name, String type, java.util.Map<String, String> __ctx, Ice.Callback __cb)
    {
        return begin_create_item(name, type, __ctx, true, __cb);
    }

    public Ice.AsyncResult begin_create_item(String name, String type, Callback_AFactory_create_item __cb)
    {
        return begin_create_item(name, type, null, false, __cb);
    }

    public Ice.AsyncResult begin_create_item(String name, String type, java.util.Map<String, String> __ctx, Callback_AFactory_create_item __cb)
    {
        return begin_create_item(name, type, __ctx, true, __cb);
    }

    private Ice.AsyncResult begin_create_item(String name, String type, java.util.Map<String, String> __ctx, boolean __explicitCtx, IceInternal.CallbackBase __cb)
    {
        __checkAsyncTwowayOnly(__create_item_name);
        IceInternal.OutgoingAsync __result = new IceInternal.OutgoingAsync(this, __create_item_name, __cb);
        try
        {
            __result.__prepare(__create_item_name, Ice.OperationMode.Normal, __ctx, __explicitCtx);
            IceInternal.BasicStream __os = __result.__startWriteParams(Ice.FormatType.DefaultFormat);
            __os.writeString(name);
            __os.writeString(type);
            __result.__endWriteParams();
            __result.__send(true);
        }
        catch(Ice.LocalException __ex)
        {
            __result.__exceptionAsync(__ex);
        }
        return __result;
    }

    public ItemPrx end_create_item(Ice.AsyncResult __result)
        throws ItemAlreadyExists
    {
        Ice.AsyncResult.__check(__result, this, __create_item_name);
        boolean __ok = __result.__wait();
        try
        {
            if(!__ok)
            {
                try
                {
                    __result.__throwUserException();
                }
                catch(ItemAlreadyExists __ex)
                {
                    throw __ex;
                }
                catch(Ice.UserException __ex)
                {
                    throw new Ice.UnknownUserException(__ex.ice_name(), __ex);
                }
            }
            IceInternal.BasicStream __is = __result.__startReadParams();
            ItemPrx __ret;
            __ret = ItemPrxHelper.__read(__is);
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

    private static final String __release_item_name = "release_item";

    public void release_item(String name)
        throws ItemNotExists
    {
        release_item(name, null, false);
    }

    public void release_item(String name, java.util.Map<String, String> __ctx)
        throws ItemNotExists
    {
        release_item(name, __ctx, true);
    }

    private void release_item(String name, java.util.Map<String, String> __ctx, boolean __explicitCtx)
        throws ItemNotExists
    {
        if(__explicitCtx && __ctx == null)
        {
            __ctx = _emptyContext;
        }
        final Ice.Instrumentation.InvocationObserver __observer = IceInternal.ObserverHelper.get(this, "release_item", __ctx);
        int __cnt = 0;
        try
        {
            while(true)
            {
                Ice._ObjectDel __delBase = null;
                try
                {
                    __checkTwowayOnly("release_item");
                    __delBase = __getDelegate(false);
                    _AFactoryDel __del = (_AFactoryDel)__delBase;
                    __del.release_item(name, __ctx, __observer);
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

    public Ice.AsyncResult begin_release_item(String name)
    {
        return begin_release_item(name, null, false, null);
    }

    public Ice.AsyncResult begin_release_item(String name, java.util.Map<String, String> __ctx)
    {
        return begin_release_item(name, __ctx, true, null);
    }

    public Ice.AsyncResult begin_release_item(String name, Ice.Callback __cb)
    {
        return begin_release_item(name, null, false, __cb);
    }

    public Ice.AsyncResult begin_release_item(String name, java.util.Map<String, String> __ctx, Ice.Callback __cb)
    {
        return begin_release_item(name, __ctx, true, __cb);
    }

    public Ice.AsyncResult begin_release_item(String name, Callback_AFactory_release_item __cb)
    {
        return begin_release_item(name, null, false, __cb);
    }

    public Ice.AsyncResult begin_release_item(String name, java.util.Map<String, String> __ctx, Callback_AFactory_release_item __cb)
    {
        return begin_release_item(name, __ctx, true, __cb);
    }

    private Ice.AsyncResult begin_release_item(String name, java.util.Map<String, String> __ctx, boolean __explicitCtx, IceInternal.CallbackBase __cb)
    {
        __checkAsyncTwowayOnly(__release_item_name);
        IceInternal.OutgoingAsync __result = new IceInternal.OutgoingAsync(this, __release_item_name, __cb);
        try
        {
            __result.__prepare(__release_item_name, Ice.OperationMode.Normal, __ctx, __explicitCtx);
            IceInternal.BasicStream __os = __result.__startWriteParams(Ice.FormatType.DefaultFormat);
            __os.writeString(name);
            __result.__endWriteParams();
            __result.__send(true);
        }
        catch(Ice.LocalException __ex)
        {
            __result.__exceptionAsync(__ex);
        }
        return __result;
    }

    public void end_release_item(Ice.AsyncResult __result)
        throws ItemNotExists
    {
        Ice.AsyncResult.__check(__result, this, __release_item_name);
        boolean __ok = __result.__wait();
        try
        {
            if(!__ok)
            {
                try
                {
                    __result.__throwUserException();
                }
                catch(ItemNotExists __ex)
                {
                    throw __ex;
                }
                catch(Ice.UserException __ex)
                {
                    throw new Ice.UnknownUserException(__ex.ice_name(), __ex);
                }
            }
            __result.__readEmptyParams();
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

    private static final String __take_item_name = "take_item";

    public ItemPrx take_item(String name)
        throws ItemBusy,
               ItemNotExists
    {
        return take_item(name, null, false);
    }

    public ItemPrx take_item(String name, java.util.Map<String, String> __ctx)
        throws ItemBusy,
               ItemNotExists
    {
        return take_item(name, __ctx, true);
    }

    private ItemPrx take_item(String name, java.util.Map<String, String> __ctx, boolean __explicitCtx)
        throws ItemBusy,
               ItemNotExists
    {
        if(__explicitCtx && __ctx == null)
        {
            __ctx = _emptyContext;
        }
        final Ice.Instrumentation.InvocationObserver __observer = IceInternal.ObserverHelper.get(this, "take_item", __ctx);
        int __cnt = 0;
        try
        {
            while(true)
            {
                Ice._ObjectDel __delBase = null;
                try
                {
                    __checkTwowayOnly("take_item");
                    __delBase = __getDelegate(false);
                    _AFactoryDel __del = (_AFactoryDel)__delBase;
                    return __del.take_item(name, __ctx, __observer);
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

    public Ice.AsyncResult begin_take_item(String name)
    {
        return begin_take_item(name, null, false, null);
    }

    public Ice.AsyncResult begin_take_item(String name, java.util.Map<String, String> __ctx)
    {
        return begin_take_item(name, __ctx, true, null);
    }

    public Ice.AsyncResult begin_take_item(String name, Ice.Callback __cb)
    {
        return begin_take_item(name, null, false, __cb);
    }

    public Ice.AsyncResult begin_take_item(String name, java.util.Map<String, String> __ctx, Ice.Callback __cb)
    {
        return begin_take_item(name, __ctx, true, __cb);
    }

    public Ice.AsyncResult begin_take_item(String name, Callback_AFactory_take_item __cb)
    {
        return begin_take_item(name, null, false, __cb);
    }

    public Ice.AsyncResult begin_take_item(String name, java.util.Map<String, String> __ctx, Callback_AFactory_take_item __cb)
    {
        return begin_take_item(name, __ctx, true, __cb);
    }

    private Ice.AsyncResult begin_take_item(String name, java.util.Map<String, String> __ctx, boolean __explicitCtx, IceInternal.CallbackBase __cb)
    {
        __checkAsyncTwowayOnly(__take_item_name);
        IceInternal.OutgoingAsync __result = new IceInternal.OutgoingAsync(this, __take_item_name, __cb);
        try
        {
            __result.__prepare(__take_item_name, Ice.OperationMode.Normal, __ctx, __explicitCtx);
            IceInternal.BasicStream __os = __result.__startWriteParams(Ice.FormatType.DefaultFormat);
            __os.writeString(name);
            __result.__endWriteParams();
            __result.__send(true);
        }
        catch(Ice.LocalException __ex)
        {
            __result.__exceptionAsync(__ex);
        }
        return __result;
    }

    public ItemPrx end_take_item(Ice.AsyncResult __result)
        throws ItemBusy,
               ItemNotExists
    {
        Ice.AsyncResult.__check(__result, this, __take_item_name);
        boolean __ok = __result.__wait();
        try
        {
            if(!__ok)
            {
                try
                {
                    __result.__throwUserException();
                }
                catch(ItemBusy __ex)
                {
                    throw __ex;
                }
                catch(ItemNotExists __ex)
                {
                    throw __ex;
                }
                catch(Ice.UserException __ex)
                {
                    throw new Ice.UnknownUserException(__ex.ice_name(), __ex);
                }
            }
            IceInternal.BasicStream __is = __result.__startReadParams();
            ItemPrx __ret;
            __ret = ItemPrxHelper.__read(__is);
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

    public static AFactoryPrx checkedCast(Ice.ObjectPrx __obj)
    {
        AFactoryPrx __d = null;
        if(__obj != null)
        {
            if(__obj instanceof AFactoryPrx)
            {
                __d = (AFactoryPrx)__obj;
            }
            else
            {
                if(__obj.ice_isA(ice_staticId()))
                {
                    AFactoryPrxHelper __h = new AFactoryPrxHelper();
                    __h.__copyFrom(__obj);
                    __d = __h;
                }
            }
        }
        return __d;
    }

    public static AFactoryPrx checkedCast(Ice.ObjectPrx __obj, java.util.Map<String, String> __ctx)
    {
        AFactoryPrx __d = null;
        if(__obj != null)
        {
            if(__obj instanceof AFactoryPrx)
            {
                __d = (AFactoryPrx)__obj;
            }
            else
            {
                if(__obj.ice_isA(ice_staticId(), __ctx))
                {
                    AFactoryPrxHelper __h = new AFactoryPrxHelper();
                    __h.__copyFrom(__obj);
                    __d = __h;
                }
            }
        }
        return __d;
    }

    public static AFactoryPrx checkedCast(Ice.ObjectPrx __obj, String __facet)
    {
        AFactoryPrx __d = null;
        if(__obj != null)
        {
            Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
            try
            {
                if(__bb.ice_isA(ice_staticId()))
                {
                    AFactoryPrxHelper __h = new AFactoryPrxHelper();
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

    public static AFactoryPrx checkedCast(Ice.ObjectPrx __obj, String __facet, java.util.Map<String, String> __ctx)
    {
        AFactoryPrx __d = null;
        if(__obj != null)
        {
            Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
            try
            {
                if(__bb.ice_isA(ice_staticId(), __ctx))
                {
                    AFactoryPrxHelper __h = new AFactoryPrxHelper();
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

    public static AFactoryPrx uncheckedCast(Ice.ObjectPrx __obj)
    {
        AFactoryPrx __d = null;
        if(__obj != null)
        {
            if(__obj instanceof AFactoryPrx)
            {
                __d = (AFactoryPrx)__obj;
            }
            else
            {
                AFactoryPrxHelper __h = new AFactoryPrxHelper();
                __h.__copyFrom(__obj);
                __d = __h;
            }
        }
        return __d;
    }

    public static AFactoryPrx uncheckedCast(Ice.ObjectPrx __obj, String __facet)
    {
        AFactoryPrx __d = null;
        if(__obj != null)
        {
            Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
            AFactoryPrxHelper __h = new AFactoryPrxHelper();
            __h.__copyFrom(__bb);
            __d = __h;
        }
        return __d;
    }

    public static final String[] __ids =
    {
        "::Ice::Object",
        "::MiddlewareTestbed::AFactory"
    };

    public static String ice_staticId()
    {
        return __ids[1];
    }

    protected Ice._ObjectDelM __createDelegateM()
    {
        return new _AFactoryDelM();
    }

    protected Ice._ObjectDelD __createDelegateD()
    {
        return new _AFactoryDelD();
    }

    public static void __write(IceInternal.BasicStream __os, AFactoryPrx v)
    {
        __os.writeProxy(v);
    }

    public static AFactoryPrx __read(IceInternal.BasicStream __is)
    {
        Ice.ObjectPrx proxy = __is.readProxy();
        if(proxy != null)
        {
            AFactoryPrxHelper result = new AFactoryPrxHelper();
            result.__copyFrom(proxy);
            return result;
        }
        return null;
    }

    public static final long serialVersionUID = 0L;
}