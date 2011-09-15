Three different implementations of a stateful fluent interface detecting invalid structure at compile time.

These are based on the responses to a [stack overflow question](http://stackoverflow.com/questions/7413643/disable-functions-inside-templated-class).

The idea behind this example is to simulate how a Fluent interface might be used to set up http request.

 * A request needs a Url.
 * It must also be either a POST request or a GET request. 
 * If its a POST it can have an arbitrary number of Key-Value pairs added as data.

This means the following code should compile

      FluentConfigCore fcc;
      FluentConfigState<ZZZState>(&fcc)
	.SetUrl("blue")
	.SetPost()
	.SetPostData("a","1")
	.SetPostData("b","2");

But this should not

      FluentConfigState<ZZZState>(&fcc)
	.SetUrl("blue")
	.SetGet()
	.SetPostData("a","1")
	.SetPostData("b","2");

The interesting differences between the 3 methods is 

 # How they work
 # What kind of error messages we get back

My answer, the `fluent_ma.cpp` gives this error message using `clang++` :

     fluent_interface3.cpp:262:6: error: no member named 'SetPostData' in 'FluentConfigState<UGZState>'
       .SetPostData("a","1")
	^

visitors answer, `fluent_visitor.cpp` gives this:

    fluent_interface.cpp:39:38: error: no type named 'AfterUrl' in 'nullState'
	FluentConfigState<typename STATE::AfterUrl> SetUrl( std::string s )
			  ~~~~~~~~~~~~~~~~^~~~~~~~
    fluent_interface.cpp:135:6: note: in instantiation of template class 'FluentConfigState<nullState>' requested here
	.SetPostData("a","1")
	 ^

ymetts answer, `fluent_ymett.cpp` gives this:

    fluent_interface2.cpp:106:47: error: no type named 'AfterPostData' in 'UGZState'
       return FluentConfigState<typename STATE::AfterPostData>( data );
				~~~~~~~~~~~~~~~~^~~~~~~~~~~~~
    fluent_interface2.cpp:180:6: note: in instantiation of member function 'FluentConfigState<UGZState>::SetPostData' requested here
	.SetPostData("a","1")
	 ^






