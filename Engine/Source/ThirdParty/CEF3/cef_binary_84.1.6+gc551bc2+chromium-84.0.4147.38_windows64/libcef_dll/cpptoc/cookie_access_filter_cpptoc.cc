// Copyright (c) 2020 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=669e20095016a2e40a0925b9715fc0b15229ff32$
//

#include "libcef_dll/cpptoc/cookie_access_filter_cpptoc.h"
#include "libcef_dll/ctocpp/browser_ctocpp.h"
#include "libcef_dll/ctocpp/frame_ctocpp.h"
#include "libcef_dll/ctocpp/request_ctocpp.h"
#include "libcef_dll/ctocpp/response_ctocpp.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK
cookie_access_filter_can_send_cookie(struct _cef_cookie_access_filter_t* self,
                                     cef_browser_t* browser,
                                     cef_frame_t* frame,
                                     cef_request_t* request,
                                     const struct _cef_cookie_t* cookie) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: request; type: refptr_diff
  DCHECK(request);
  if (!request)
    return 0;
  // Verify param: cookie; type: struct_byref_const
  DCHECK(cookie);
  if (!cookie)
    return 0;
  // Unverified params: browser, frame

  // Translate param: cookie; type: struct_byref_const
  CefCookie cookieObj;
  if (cookie)
    cookieObj.Set(*cookie, false);

  // Execute
  bool _retval = CefCookieAccessFilterCppToC::Get(self)->CanSendCookie(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefRequestCToCpp::Wrap(request), cookieObj);

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK
cookie_access_filter_can_save_cookie(struct _cef_cookie_access_filter_t* self,
                                     cef_browser_t* browser,
                                     cef_frame_t* frame,
                                     cef_request_t* request,
                                     struct _cef_response_t* response,
                                     const struct _cef_cookie_t* cookie) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: request; type: refptr_diff
  DCHECK(request);
  if (!request)
    return 0;
  // Verify param: response; type: refptr_diff
  DCHECK(response);
  if (!response)
    return 0;
  // Verify param: cookie; type: struct_byref_const
  DCHECK(cookie);
  if (!cookie)
    return 0;
  // Unverified params: browser, frame

  // Translate param: cookie; type: struct_byref_const
  CefCookie cookieObj;
  if (cookie)
    cookieObj.Set(*cookie, false);

  // Execute
  bool _retval = CefCookieAccessFilterCppToC::Get(self)->CanSaveCookie(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefRequestCToCpp::Wrap(request), CefResponseCToCpp::Wrap(response),
      cookieObj);

  // Return type: bool
  return _retval;
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefCookieAccessFilterCppToC::CefCookieAccessFilterCppToC() {
  GetStruct()->can_send_cookie = cookie_access_filter_can_send_cookie;
  GetStruct()->can_save_cookie = cookie_access_filter_can_save_cookie;
}

// DESTRUCTOR - Do not edit by hand.

CefCookieAccessFilterCppToC::~CefCookieAccessFilterCppToC() {}

template <>
CefRefPtr<CefCookieAccessFilter> CefCppToCRefCounted<
    CefCookieAccessFilterCppToC,
    CefCookieAccessFilter,
    cef_cookie_access_filter_t>::UnwrapDerived(CefWrapperType type,
                                               cef_cookie_access_filter_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType CefCppToCRefCounted<CefCookieAccessFilterCppToC,
                                   CefCookieAccessFilter,
                                   cef_cookie_access_filter_t>::kWrapperType =
    WT_COOKIE_ACCESS_FILTER;