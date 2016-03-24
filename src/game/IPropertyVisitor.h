#ifndef IPROPERTYVISITOR_H_INCLUDED
#define IPROPERTYVISITOR_H_INCLUDED

namespace game
{
	/*! \class IPropertyVisitor
		\brief Class for visiting all properties of a game object.
		\details Use this class to iterate over all properties of
					e.g. a GameObject.
	*/
	class IPropertyVisitor
	{
	public:
		virtual ~IPropertyVisitor();
        virtual void onProperty(const char* name, float value) {};
        virtual void onProperty(const char* name, const std::string& value) {};
        virtual void onProperty(const char* name, const b2Vec2& value) {};

        template<class T>
        void operator()(const char* name, T&& t)
        {
        	onProperty(name, std::forward<T>(t));
        }
	};
}

#endif // IPROPERTYVISITOR_H_INCLUDED
