
// 支持以宏为参数的拼接

#define COMBINE_(a, b)          COMBINE_IMPL_(a, b)
#define COMBINE_IMPL_(a, b)     a##b


// 代理接口

#define I_DELEGATE_             COMBINE_(IDelegate, SUFFIX_)

// 代理实现

#define FUNC_DELEGATE_          COMBINE_(FuncDelegate, SUFFIX_)
#define METHOD_DELEGATE_        COMBINE_(MethodDelegate, SUFFIX_)
#define FUNCTOR_DELEGATE_       COMBINE_(FunctorDelegate, SUFFIX_)

// 单代理，多代理，实际使用的对象，保存一个或多个代理实现

#define DELEGATE_               COMBINE_(Delegate, SUFFIX_)
#define MULTI_DELEGATE_         COMBINE_(MultiDelegate, SUFFIX_)

// 代理接口

TEMPLATE_ TEMPLATE_PARAMS_
class I_DELEGATE_
{
public:
    virtual ~I_DELEGATE_() {}
    virtual bool IsType(const std::type_info& type) = 0;
    virtual void Invoke(PARAMS_) = 0;
    virtual bool Equal(I_DELEGATE_ TEMPLATE_ARGS_* other) const = 0;
};


// 函数代理（一般函数和类静态函数）

TEMPLATE_ TEMPLATE_PARAMS_
class FUNC_DELEGATE_ : public I_DELEGATE_ TEMPLATE_ARGS_
{
public:
    typedef void (*Func)(PARAMS_);

    FUNC_DELEGATE_(Func func) : func_(func) {}

    virtual bool IsType(const std::type_info& type) {
        return typeid(FUNC_DELEGATE_ TEMPLATE_ARGS_) == type; }

    virtual void Invoke(PARAMS_) { func_(ARGS_); }

    virtual bool Equal(I_DELEGATE_ TEMPLATE_ARGS_* other) const
    {
        if (0 == other || !other->IsType(typeid(FUNC_DELEGATE_ TEMPLATE_ARGS_)))
            return false;

        FUNC_DELEGATE_ TEMPLATE_ARGS_ * cast = static_cast<FUNC_DELEGATE_ TEMPLATE_ARGS_*>(other);
        return cast->func_ == func_;
    }

private:
    Func func_;
};

// 非静态类函数代理（即调用约定为 __thiscall 的函数）

template CLASS_TEMPLATE_PARAMS_
class METHOD_DELEGATE_ : public I_DELEGATE_ TEMPLATE_ARGS_
{
public:
    typedef void(T::*Method)(PARAMS_);

    METHOD_DELEGATE_(T& obj, Method method) : obj_(obj), method_(method) {}

    virtual bool IsType(const std::type_info& type) { 
        return typeid(METHOD_DELEGATE_ CLASS_TEMPLATE_ARGS_) == type; }

    virtual void Invoke(PARAMS_) { (obj_.*method_)(ARGS_); }

    virtual bool Equal(I_DELEGATE_ TEMPLATE_ARGS_* other) const
    {
        if (0 == other || !other->IsType(typeid(METHOD_DELEGATE_ CLASS_TEMPLATE_ARGS_)))
            return false;

        METHOD_DELEGATE_ CLASS_TEMPLATE_ARGS_ * cast = 
            static_cast<METHOD_DELEGATE_ CLASS_TEMPLATE_ARGS_ *>(other);
        return ((&(cast->obj_)) == (&obj_)) && (cast->method_ == method_);
    }

private:
    T& obj_;
    Method method_;
};

// 仿函数代理（代理拷贝整个仿函数）

template CLASS_TEMPLATE_PARAMS_
class FUNCTOR_DELEGATE_ : public I_DELEGATE_ TEMPLATE_ARGS_
{
public:
    typedef void(T::*Method)(PARAMS_);

    FUNCTOR_DELEGATE_(const T& obj, Method method) : obj_(obj), method_(method) {}

    virtual bool IsType(const std::type_info& type) { 
        return typeid(FUNCTOR_DELEGATE_ CLASS_TEMPLATE_ARGS_) == type; }

    virtual void Invoke(PARAMS_) { (obj_.*method_)(ARGS_); }

    // 此代理保存的是函数对象的一份拷贝，故不存在相等的两份代理，Equal 永远返回 false

    virtual bool Equal(I_DELEGATE_ TEMPLATE_ARGS_* other) const { return false; }

private:
    T obj_;
    Method method_;
};


// 单代理，实际中使用的对象

TEMPLATE_ TEMPLATE_PARAMS_
class DELEGATE_
{
public:
    typedef I_DELEGATE_ TEMPLATE_ARGS_ IDelegate;

    DELEGATE_() : delegate_() {}

    // 会转移 other 的所有权到本对象

    DELEGATE_(const DELEGATE_ TEMPLATE_ARGS_ & other)
    {
        delegate_ = other.delegate_;
        const_cast<DELEGATE_ TEMPLATE_ARGS_ &>(other).delegate_ = 0;
    }

    ~DELEGATE_ () { Clear(); }

    DELEGATE_ TEMPLATE_ARGS_ & operator = (IDelegate* delegate)
    {
        delete delegate_;
        delegate_ = delegate;
        return *this;
    }

    // 会转移 other 的所有权到本对象

    DELEGATE_ TEMPLATE_ARGS_& operator = (const DELEGATE_ TEMPLATE_ARGS_ & other)
    {
        delete delegate_;
        delegate_ = other.delegate_;
        const_cast<DELEGATE_  TEMPLATE_ARGS_&>(other).delegate_ = 0;
        return *this;
    }

    void operator()(PARAMS_)
    {
        if (delegate_ == 0) 
            return;
        delegate_->Invoke(ARGS_);
    }

    bool Empty() const { return delegate_ == 0; }

    void Clear()
    {
        if (delegate_)
        {
            delete delegate_;
            delegate_ = 0;
        }
    }

private:
    IDelegate* delegate_;
};

// 多代理，实际中使用的对象

TEMPLATE_ TEMPLATE_PARAMS_
class MULTI_DELEGATE_
{
public:
    typedef I_DELEGATE_ TEMPLATE_ARGS_              IDelegate;
    typedef TYPENAME_ std::list<IDelegate*>         Delegates;
    typedef TYPENAME_ Delegates::iterator           DelegatesIterator;
    typedef TYPENAME_ Delegates::const_iterator     ConstDelegatesIterator;

    MULTI_DELEGATE_() {}
    ~MULTI_DELEGATE_() { Clear(); }

    MULTI_DELEGATE_ TEMPLATE_ARGS_ & operator += (IDelegate* other)
    {
        DelegatesIterator i = elegates_.begin();
        DelegatesIterator end = elegates_.end();
        while (i != end)
        {
            if ((*i) && (*i)->Equal(other))
                assert(false);
            ++i;
        }

        elegates_.push_back(other);

        return *this;
    }

    MULTI_DELEGATE_ TEMPLATE_ARGS_ & operator -= (IDelegate* other)
    {
        DelegatesIterator i = elegates_.begin();
        DelegatesIterator end = elegates_.end();
        while (i != end)
        {
            if ((*i) && (*i)->Equal(other))
            {
                if ((*i) != other) 
                    delete (*i);
                (*i) = 0;
                break;
            }
            ++i;
        }

        delete other;

        return *this;
    }

    void operator()(PARAMS_)
    {
        DelegatesIterator i = elegates_.begin();
        DelegatesIterator end = elegates_.end();
        while (i != end)
        {
            if (0 == (*i))
                i = elegates_.erase(i);
            else
            {
                (*i)->Invoke(ARGS_);
                ++i;
            }
        }
    }

    bool Empty() const
    {
        ConstDelegatesIterator i = elegates_.begin();
        ConstDelegatesIterator end = elegates_.end();
        while (i != end)
        {
            if (*i) 
                return false;
            ++i;
        }

        return true;
    }

    void Clear()
    {
        DelegatesIterator i = elegates_.begin();
        DelegatesIterator end = elegates_.end();
        while (i != end)
        {
            if (*i)
            {
                delete (*i);
                (*i) = 0;
            }
            ++i;
        }
    }

private:
    // constructor and operator = , without implementation, just for private
    MULTI_DELEGATE_(const MULTI_DELEGATE_ TEMPLATE_ARGS_ & other);
    MULTI_DELEGATE_ TEMPLATE_ARGS_ & operator = (const MULTI_DELEGATE_ TEMPLATE_ARGS_ & other);

private:
    Delegates elegates_;
};

// New 一个函数代理，返回 IDelegateX 接口
// NewDelegate(func)
// NewDelegate(class::static_method)

TEMPLATE_ TEMPLATE_PARAMS_
inline I_DELEGATE_ TEMPLATE_ARGS_ * NewDelegate(void (*func)(PARAMS_))
{
    return new FUNC_DELEGATE_ TEMPLATE_ARGS_ (func);
}

// New 一个非静态成员函数代理，返回 IDelegateX 接口
// NewDelegate(&obj, &class::method)

template CLASS_TEMPLATE_PARAMS_
inline I_DELEGATE_ TEMPLATE_ARGS_ * NewDelegate(T* obj, void (T::*method)(PARAMS_))
{
    return new METHOD_DELEGATE_ CLASS_TEMPLATE_ARGS_ (*obj, method);
}

// New 一个仿函数代理，返回 IDelegateX 接口
// NewDelegate(obj, &class::method)

template CLASS_TEMPLATE_PARAMS_
inline I_DELEGATE_ TEMPLATE_ARGS_ * NewDelegate(const T& obj, void (T::*method)(PARAMS_))
{
    return new FUNCTOR_DELEGATE_ CLASS_TEMPLATE_ARGS_ (obj, method);
}

#undef COMBINE_
#undef COMBINE_IMPL_

#undef I_DELEGATE_

#undef FUNC_DELEGATE_
#undef METHOD_DELEGATE_

#undef DELEGATE_
#undef MULTI_DELEGATE_

#undef SUFFIX_
#undef TEMPLATE_
#undef TEMPLATE_PARAMS_
#undef TEMPLATE_ARGS_
#undef CLASS_TEMPLATE_PARAMS_
#undef CLASS_TEMPLATE_ARGS_
#undef PARAMS_
#undef ARGS_
#undef TYPENAME_


