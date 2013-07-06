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

public abstract class _ItemCDisp extends Ice.ObjectImpl implements ItemC
{
    protected void
    ice_copyStateFrom(Ice.Object __obj)
        throws java.lang.CloneNotSupportedException
    {
        throw new java.lang.CloneNotSupportedException();
    }

    public static final String[] __ids =
    {
        "::Ice::Object",
        "::MiddlewareTestbed::Item",
        "::MiddlewareTestbed::ItemC"
    };

    public boolean ice_isA(String s)
    {
        return java.util.Arrays.binarySearch(__ids, s) >= 0;
    }

    public boolean ice_isA(String s, Ice.Current __current)
    {
        return java.util.Arrays.binarySearch(__ids, s) >= 0;
    }

    public String[] ice_ids()
    {
        return __ids;
    }

    public String[] ice_ids(Ice.Current __current)
    {
        return __ids;
    }

    public String ice_id()
    {
        return __ids[2];
    }

    public String ice_id(Ice.Current __current)
    {
        return __ids[2];
    }

    public static String ice_staticId()
    {
        return __ids[2];
    }

    public final int get_item_age()
    {
        return get_item_age(null);
    }

    public final String name()
    {
        return name(null);
    }

    public final void actionC(int a1, Ice.IntHolder a2, Ice.ShortHolder b)
    {
        actionC(a1, a2, b, null);
    }

    public static Ice.DispatchStatus ___actionC(ItemC __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
        __checkMode(Ice.OperationMode.Normal, __current.mode);
        IceInternal.BasicStream __is = __inS.startReadParams();
        int a1;
        a1 = __is.readInt();
        __inS.endReadParams();
        Ice.IntHolder a2 = new Ice.IntHolder();
        Ice.ShortHolder b = new Ice.ShortHolder();
        __obj.actionC(a1, a2, b, __current);
        IceInternal.BasicStream __os = __inS.__startWriteParams(Ice.FormatType.DefaultFormat);
        __os.writeInt(a2.value);
        __os.writeShort(b.value);
        __inS.__endWriteParams(true);
        return Ice.DispatchStatus.DispatchOK;
    }

    private final static String[] __all =
    {
        "actionC",
        "get_item_age",
        "ice_id",
        "ice_ids",
        "ice_isA",
        "ice_ping",
        "name"
    };

    public Ice.DispatchStatus __dispatch(IceInternal.Incoming in, Ice.Current __current)
    {
        int pos = java.util.Arrays.binarySearch(__all, __current.operation);
        if(pos < 0)
        {
            throw new Ice.OperationNotExistException(__current.id, __current.facet, __current.operation);
        }

        switch(pos)
        {
            case 0:
            {
                return ___actionC(this, in, __current);
            }
            case 1:
            {
                return _ItemDisp.___get_item_age(this, in, __current);
            }
            case 2:
            {
                return ___ice_id(this, in, __current);
            }
            case 3:
            {
                return ___ice_ids(this, in, __current);
            }
            case 4:
            {
                return ___ice_isA(this, in, __current);
            }
            case 5:
            {
                return ___ice_ping(this, in, __current);
            }
            case 6:
            {
                return _ItemDisp.___name(this, in, __current);
            }
        }

        assert(false);
        throw new Ice.OperationNotExistException(__current.id, __current.facet, __current.operation);
    }

    protected void __writeImpl(IceInternal.BasicStream __os)
    {
        __os.startWriteSlice(ice_staticId(), -1, true);
        __os.endWriteSlice();
    }

    protected void __readImpl(IceInternal.BasicStream __is)
    {
        __is.startReadSlice();
        __is.endReadSlice();
    }

    public static final long serialVersionUID = 0L;
}
