So after my previous post I finally got around and finished my little C++ project. Just to avoid any bitching, I have to say one more time that this is my first attempt in C++. So here goes!

So I've started building something like an Asterisk Event Collector. The whole idea is rather simple; you have a process listening at the Asterisk AJAM interface, and you intercept all the events that occur in an asterisk. You specify a Filter to explicitly collect some of the events, and you pass them down to the processor for further handling. 

So this is my first version of ShiftNine. (Geek joke, considering my PHP Asterisk library called <a href="https://github.com/twmobius/Shift8/">Shift8</a>, whereas Shift9 is just Shift8++) 

I think I've done a decent job with this one to begin with (considering my days of experience in C++). I've separated the library stuff from the application stuff creating a ShiftNine library that any other application can use. I've used the <a href="http://en.wikipedia.org/wiki/Observer_pattern">Observer Pattern</a> for my Processors and something like a Filter Pattern from my Java days. 

So say one needs to create an application that when a new call is being added to a Queue to raise an alert to the agents behind a call center. One should create a new class that implements the ShiftNineFilter class. 

```
class QueueEntryFilter: public ShiftNineFilter {
        public:
                bool valid( std::string event ) {
                     if( event.find("QueueEntry") != std::string::npos ) 
                            return 1;

                     return 0;
               }
```

Then you create a processor that will actually raise the alert on QueueEntry:

```
class QueueEntryNotify: public ShiftNineProcessor {
        public:
                bool process( ShiftNineAsteriskEvent *event ) {
                        // Add code here to raise the alert.
                }
}
```

And finally merge the two:
```
                        ShiftNine _proxy("http://<ajam>", "manager", "secret");

                        QueueEntryFilter _filter;
                        QueueEntryProcessor _processor;

                        _proxy.setFilter(&_filter);
                        _proxy.setProcessor(&_processor);

                        try {
                                _proxy.login();

                                for( ;; ) {
                                        _proxy.waitEvent();
                                }
                        } catch( ShiftNineException &er ) {
                                cout << "[Error]: ShiftNine Library error: " << er.what() << endl;
                                _proxy.logoff();
                                return 1;
                        }
```

And that's pretty much it.

I know that there are a few issues with ShiftNine, which I will try and fix if needed:
* ShiftNine is not thread safe. This is because I am using curl_share without locks
* MySQLProcessor included does not escape the values added in the database - This could be dangerous.
