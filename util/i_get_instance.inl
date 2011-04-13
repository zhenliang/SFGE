
template <class T>
T& util::IGetInstance<T>::GetInstance()
{
	static T instance;
	return instance;
}