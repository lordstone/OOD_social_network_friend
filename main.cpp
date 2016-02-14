typedef class socialUser{
public:

    typedef socialUser user_t;
    string userName;
    unordered_set<user_t*> friendList;
    static void addFriends(user_t * a, user_t * b){
        a -> addFriend(b);
        b -> addFriend(a);
    }

    static void deleteFriends(user_t * a, user_t * b){
        a -> deleteFriend(b);
        b -> deleteFriend(a);
    }

    static bool isAcquaintances(user_t * a, user_t * b){
        bool res1 = a -> isAcquaintance(b);
        if(res1) return true;
        return b -> isAcquaintance(a);
    }

    void printAll(){
        if(friendList.empty()){
            cout << userName + " has no friends" << endl;
            return;
        }
        cout << userName + " has the following network:" << endl;
        unordered_set<user_t*> mySet;
        mySet.insert(this);
        DFS_print(this, mySet, 0);
    }

    void printFriends(){
        if(friendList.empty()){
            cout << "No friends" << endl;
            return;
        }
        for(auto i : friendList){
            cout << userName << " has a friend " << i -> userName << endl;
        }
    }

    socialUser(){
        userName = "";
        lvlAcq = 5;
    }

    socialUser(string name){
        userName = name;
        lvlAcq = 5;
    }

    socialUser(string name, int lvl){
        userName = name;
        lvlAcq = lvl;
    }

    void addFriend(socialUser * userTwo){
        if(friendList.find(userTwo) == friendList.end()){
            friendList.insert(userTwo);
            //userTwo -> addFriend(this);
        }
    }

    void deleteFriend(socialUser * userTwo){
        if(friendList.find(userTwo) != friendList.end()){
            friendList.erase(userTwo);
        }
    }

    bool isFriend(socialUser * userTwo){
        return (friendList.find(userTwo) != friendList.end());
    }

    bool isAcquaintance(socialUser * userTwo){
        if(isFriend(userTwo)) return true;
        if(lvlAcq <= 1) return false;
        for(auto i : friendList){
            bool res = i -> isAcquaintance(userTwo, lvlAcq - 1);
            if(res) return true;
        }
        return false;
    }

    bool isAcquaintance(socialUser * userTwo, int lvlLeft){
        if(isFriend(userTwo)) return true;
        if(lvlLeft <= 1) return false;
        for(auto i : friendList){
            bool res = i -> isAcquaintance(userTwo, lvlLeft - 1);
            if(res) return true;
        }
        return false;
    }

private:

    void DFS_print(user_t * myUser, unordered_set<user_t*>& mySet, int level){
        if(myUser == NULL) {
            return;
        }
        for(auto i : myUser -> friendList){
            for (int j = 0; j < level; j ++) cout << "----" ;
            cout << "->" ;
            cout << myUser -> userName + " has friend " + i -> userName << endl;
            if(mySet.find(i)== mySet.end()){
                mySet.insert(i);
                DFS_print(i, mySet, level + 1);
            }
        }
    }

    int lvlAcq;
}user_t;


int main(){

    user_t * a = new user_t("Frank");
    user_t * b = new user_t("Amy");
    user_t * c = new user_t("Lucas");
    user_t * d = new user_t("Mark");
    user_t * e = new user_t("Evelyn");
    user_t * f = new user_t("Taylor");
    user_t * g = new user_t("John");
    socialUser::addFriends(a,b);
    socialUser::addFriends(b,c);
    socialUser::addFriends(c,d);
    socialUser::addFriends(a,c);
    socialUser::addFriends(a,d);
    socialUser::addFriends(b,d);
    socialUser::addFriends(b,g);
    socialUser::addFriends(d,e);
    socialUser::addFriends(e,f);
    socialUser::addFriends(d,g);
    //a -> printFriends();
    //socialUser::deleteFriends(a,b);
    a -> printFriends();
    b -> printFriends();
    cout << "--------------" << endl;
    a -> printAll();
    cout << "--------------" << endl;
    a -> printFriends();
    b -> printFriends();
    return 0;
}
