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

public interface ItemBPrx extends ItemPrx
{
    public float actionB(String a);

    public float actionB(String a, java.util.Map<String, String> __ctx);

    public Ice.AsyncResult begin_actionB(String a);

    public Ice.AsyncResult begin_actionB(String a, java.util.Map<String, String> __ctx);

    public Ice.AsyncResult begin_actionB(String a, Ice.Callback __cb);

    public Ice.AsyncResult begin_actionB(String a, java.util.Map<String, String> __ctx, Ice.Callback __cb);

    public Ice.AsyncResult begin_actionB(String a, Callback_ItemB_actionB __cb);

    public Ice.AsyncResult begin_actionB(String a, java.util.Map<String, String> __ctx, Callback_ItemB_actionB __cb);

    public float end_actionB(Ice.AsyncResult __result);
}