    ////////////////////////////////////////////////vector<bool> trap
    {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! trap
        std::vector<bool> v(10, false);
        for (auto velem : v) { velem = true; }
        LOG(INFO) << v;        //[1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    }//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! trap
    //{     //cannot compile
    //    std::vector<bool> v(10, false);
    //    for (auto& velem : v) { velem = true; }
    //    LOG(INFO) << v;
    //}
    {
        std::vector<bool> v(10, false);
        for (auto&& velem : v) { velem = true; }
        LOG(INFO) << v;        //[1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    }
    {
        std::vector<bool> v(10, false);
        for (auto&& velem : v) { velem = true; }
        LOG(INFO) << v;        //[1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    }
    {
        std::vector<bool> v(10, false);
        for (bool velem : v) { velem = true; }
        LOG(INFO) << v;        //[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    }
    {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! trap
        std::vector<bool> v(10, false);
        for (bool&& velem : v) { velem = true; }
        LOG(INFO) << v;        //[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    }//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! trap
    {
        std::vector<int> v(10, false);
        for (auto&& velem : v) { velem = true; }
        LOG(INFO) << v;        //[1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    }
   ////////////////////////////////////////////////vector<bool> trap


