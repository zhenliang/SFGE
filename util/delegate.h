#pragma once

#include <typeinfo>
#include <list>
#include <cassert>

namespace util
{

#define SUFFIX_                 0
#define TEMPLATE_
#define TEMPLATE_PARAMS_
#define TEMPLATE_ARGS_
#define CLASS_TEMPLATE_PARAMS_  <class T>
#define CLASS_TEMPLATE_ARGS_    <T>
#define PARAMS_
#define ARGS_
#define TYPENAME_

#include "delegate_impl.h"

#define SUFFIX_                 1
#define TEMPLATE_               template
#define TEMPLATE_PARAMS_        <class TP1>
#define TEMPLATE_ARGS_          <TP1>
#define CLASS_TEMPLATE_PARAMS_  <class T, class TP1>
#define CLASS_TEMPLATE_ARGS_    <T, TP1>
#define PARAMS_                 TP1 p1
#define ARGS_                   p1
#define TYPENAME_               typename

#include "delegate_impl.h"

#define SUFFIX_                 2
#define TEMPLATE_               template
#define TEMPLATE_PARAMS_        <class TP1, class TP2>
#define TEMPLATE_ARGS_          <TP1, TP2>
#define CLASS_TEMPLATE_PARAMS_  <class T, class TP1, class TP2>
#define CLASS_TEMPLATE_ARGS_    <T, TP1, TP2>
#define PARAMS_                 TP1 p1, TP2 p2
#define ARGS_                   p1, p2
#define TYPENAME_               typename

#include "delegate_impl.h"

#define SUFFIX_                 3
#define TEMPLATE_               template
#define TEMPLATE_PARAMS_        <class TP1, class TP2, class TP3>
#define TEMPLATE_ARGS_          <TP1, TP2, TP3>
#define CLASS_TEMPLATE_PARAMS_  <class T, class TP1, class TP2, class TP3>
#define CLASS_TEMPLATE_ARGS_    <T, TP1, TP2, TP3>
#define PARAMS_                 TP1 p1, TP2 p2, TP3 p3
#define ARGS_                   p1, p2, p3
#define TYPENAME_               typename

#include "delegate_impl.h"

#define SUFFIX_                 4
#define TEMPLATE_               template
#define TEMPLATE_PARAMS_        <class TP1, class TP2, class TP3, class TP4>
#define TEMPLATE_ARGS_          <TP1, TP2, TP3, TP4>
#define CLASS_TEMPLATE_PARAMS_  <class T, class TP1, class TP2, class TP3, class TP4>
#define CLASS_TEMPLATE_ARGS_    <T, TP1, TP2, TP3, TP4>
#define PARAMS_                 TP1 p1, TP2 p2, TP3 p3, TP4 p4
#define ARGS_                   p1, p2, p3, p4
#define TYPENAME_               typename

#include "delegate_impl.h"

#define SUFFIX_                 5
#define TEMPLATE_               template
#define TEMPLATE_PARAMS_        <class TP1, class TP2, class TP3, class TP4, class TP5>
#define TEMPLATE_ARGS_          <TP1, TP2, TP3, TP4, TP5>
#define CLASS_TEMPLATE_PARAMS_  <class T, class TP1, class TP2, class TP3, class TP4, class TP5>
#define CLASS_TEMPLATE_ARGS_    <T, TP1, TP2, TP3, TP4, TP5>
#define PARAMS_                 TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5
#define ARGS_                   p1, p2, p3, p4, p5
#define TYPENAME_               typename

#include "delegate_impl.h"

}
