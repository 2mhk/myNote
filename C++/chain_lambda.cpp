template<typename T>
class Task;
template<typename R,typename...Args>
class Task<R(Args...)>{
    public:
    Task(std::function<R(Args...)> && f) : m_fn(std::move(f)){std::cout <<
    	"move construct func name : "<<__func__<< std::endl;}
    Task(std::function<R(Args...)> & f) : m_fn(f){std::cout <<"construct func name : "<<
    	__func__<< std::endl;}
    R run(Args&& ... args){
        std::cout <<"exec function,func name : "<<__func__<< std::endl;
        return m_fn(std::forward<Args>(args)...); //perfect
    }
    // continue exec
    template<typename F>
    auto then(F && f)->Task<typename std::result_of<F(R)>::type(Args...)>{
        std::cout <<"then -> "<<i<< std::endl;i++;
        using return_type = typename std::result_of<F(R)>::type; //get F return type
        auto func = std::move(m_fn);
        return Task<return_type(Args...)>([func,f](Args&& ...args){
            return f(func(std::forward<Args>(args)...));
        });
    }
    private:
    std::function<R(Args...)> m_fn;
};

void TestTask(){
    Task<int(int)> task([](int i){std::cout <<"init :"<<i<< std::endl;return i;});
    std::string str = "join in lambda then : ";
    auto res = task.then([&str](int i){str += "then 1\t";std::cout <<"first:"<<i<< 
    	std::endl;return i + 1;})
    .then([&str](int i){str += "then 2\t";std::cout <<"second:"<<i<<std::endl;return i + 2;})
    .then([&str](int n){str += "then 3\t";std::cout <<"third:"<<n<< 
    	std::endl;return std::make_tuple(n + 3,"n + 3");})
    .then([&str](auto n){str += "then 4\t";std::cout <<"fouth:"<< 
    	std::get<0>(n)<<"tuple string : "<<std::get<1>(n)<< std::endl;
    	return std::make_tuple(std::get<0>(n) + 4,"then exec ecnd");
    	}).run(1);
    std::cout <<"result tuple value : "<<std::get<0>(res)<<"   result tuple string : "<<
    	std::get<1>(res)<< "   result string : "<<str<<std::endl;
}

auto fu(int i){
    auto f = std::async([](int i){
        std::cout <<"sleep two "<<i<<" seconds..."<< std::endl;
       // std::chrono::milliseconds dre(i * 1000);
       // std::this_thread::sleep_for(dre);
        return i * i;
    },i);
    return std::forward<decltype(f)>(f);
}

void testFuture(){
    std::cout <<"at testFuture func thread : "<<std::this_thread::get_id()<< std::endl;
    typedef std::future<int> A;
    typedef std::result_of<decltype(fu)*(int)>::type B;
    static_assert(std::is_same<A,B>::value,"not equal");
    Task<std::result_of<decltype(fu)&(int)>::type(int)> task(fu);
    auto t = task.then([](auto o){
        std::cout <<"wait value ..."<< std::endl;
        std::cout <<"at first then func thread : "<<std::this_thread::get_id()<< std::endl;
        auto ii = o.get() + 100;
        auto f = std::async([](int i){
            std::cout <<"new value :"<<i<<" .."<< std::endl;
            std::cout <<"]async in thread : "<<std::this_thread::get_id()<< std::endl;
            //std::chrono::milliseconds dre(i * 1000);
            //std::this_thread::sleep_for(dre);
            return i * i;
        },ii);
        return std::forward<decltype(f)>(f);}) 
    .then([](auto o){
        std::cout <<wait value ...\n";
        std::cout <<"]at second then func thread : "<<std::this_thread::get_id<< std::endl; 
        //std::chrono::milliseconds dre(2000); //sleep 2 seconds
        //std::this_thread::sleep_for(dre);
        std::cout <<"wait last value...,,,,,,,,,,,,,,,,,,,,,,,,,,"<< std::endl;
        return o.get() + 10000;})
    .then([](auto o){
        std::cout <<"fouth then"<< std::endl;
        auto ff = std::async([](auto i){
            std::cout <<"wait value ...\n";
            std::cout <<"at third then func thread : "<<std::this_thread::get_id<< std::endl; 
            int all = 2134;
            for(auto ii = 0; ii < i; ++ii){
                //std::cout<<ii;
                all += (ii % 3 == 0 && ii > all * 1.5) ? 1 : 2;
            }
            std::cout<<""<<all<<"\n";
            return all;
        },o);
        return std::forward<decltype(ff)>(ff);})
    .run(2); // 2 seconds
    std::cout<<"future get : "<<t.get()<<"\n";
}

int main(){
    TestTask();  // lambda exec func
    testFuture(); //lambda exec thread
}

