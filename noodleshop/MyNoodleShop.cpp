#include "MyNoodleShop.h"
#include <iostream>

// This is here to avoid creating yet another object file.
NoodleShop* NoodleShop::create(int npots, int rent, int customers, std::vector<Noodle> noodles) {
  return new MyNoodleShop(npots,rent,customers,noodles);
}


// MyNoodleShop Member Functions


MyNoodleShop::MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles){
    // if(noodles.size()){
    //     std::cout<<npots <<rent<<customers;
    // }
    mypots=npots;
    mrent=rent;
    shop_noodles = noodles;
    exp_cust=customers;
    //served_cust = 0;
   // money=rent*(-1);
    
    
    /*switch (rent) {
        case 82500:{
            shop_type=0;
            break;
        }
        
        case 70000: {
            shop_type=1;
            break;
        }
        
        case 95000: {
            shop_type=2;
            break;
        }
            
        case 50000: {
            shop_type=3
            break;
        }
            
        
            default: {
            shop_type=4;
            break;
            }
    }*/
    
    for (int i=0;i<npots; i++){
        Pot temp;
        // below same as clean action
        temp.isClean = true;
        temp.noodlename = "";
        temp.cooking_mins_left = temp.time_until_stale = temp.servings_left = -1;
        shop_pots.push_back(temp);
    
    }
    // std::cout<<exp_cust;
}

std::vector<Order> MyNoodleShop::orders(int minute, std::vector<Order> orderlist) {
//    if(minute == 1){
//        std::cout<<"";
//     }
    update_currorders();
    update_pots();
    if (minute >=719){
        std::vector<Order> temp;
        return temp;
    }
    std::vector<Order> accepted_orders;
    for (unsigned long i=0;i<orderlist.size();i++){
        if (checknoodle(orderlist[i].noodle)!=-1)
            accepted_orders.push_back(orderlist[i]);
        else if (anycleanpots())
            accepted_orders.push_back(orderlist[i]);
    }
    for (unsigned long i=0;i<accepted_orders.size(); i++){
        order_detail temp;
        temp.order = accepted_orders[i];
        temp.time=0;
        temp.tip_left=100;
        curr_orders.push_back(temp);
    }
    return accepted_orders;
}
Action* MyNoodleShop::action(int minute){
    if(minute%5 == 0){
       int dirtypot = stale_empty();
           if (dirtypot != -1){
               clean_pots(dirtypot);
              // std::cout<<"CleanAction("<<dirtypot<<")"<<std::endl;
               CleanAction* temp = new CleanAction(dirtypot);
               return temp;
           }
    }

   
    std::vector<serve_info> pre_serve;
    for (unsigned long i=0;i<curr_orders.size();i++){
        int temp = noodle_cooked(curr_orders[i].order.noodle); //returns -1 if there arent any cooked noodles in the pots
        if (temp != -1) {
            if ((shop_pots[temp].time_until_stale>0) && (shop_pots[temp].cooking_mins_left==0) && (shop_pots[temp].servings_left>0)){
                serve_info a;
                a.order = curr_orders[i].order;
                a.index = i;
                pre_serve.push_back(a);
            }
            
        }
    }
    if (pre_serve.size()==0){
        if (anycleanpots()) { /*we can't cook a noodle if it takes 10 minutes to cook if it is 8:25 depending on batch size*/
            // check if the noodle we're cooking is already being cooked, if so, move on to next noodle. (if more orders coming in than orders being cooked, cook another batch)
            for(unsigned long i = 0; i<curr_orders.size(); i++){
                //if there aren't any noodles with order.noodle name being cooked, cook the noodle.
                if(noodle_cooking(curr_orders[i].order.noodle) == -1){
                    int pot_id = cooknoodle(Findnoodle(curr_orders[i].order.noodle));
                    //std::cout<<"CookAction("<<pot_id<<" "<<curr_orders[i].order.noodle<<")"<<std::endl;
                    CookAction* temp = new CookAction(pot_id,curr_orders[i].order.noodle);
                    // std::cout<<curr_orders[0].order.noodle<<std::endl; for debugging
                    return temp;
                }
            }
        }
        int dirtypot = stale_empty();
        if (dirtypot != -1){
            clean_pots(dirtypot);
           // std::cout<<"CleanAction("<<dirtypot<<")"<<std::endl;
            CleanAction* temp = new CleanAction(dirtypot);
            return temp;
        }
       // std::cout<<"NoAction()"<<std::endl;
        NoAction* temp = new NoAction();
        return temp;
    }
    else {
        std::vector<Serve> serving;
        //std::cout<<"pre_serve contains: ";
//        for(unsigned int i = 0; i<pre_serve.size(); i++){
//           // std::cout<<pre_serve[i].order.noodle<< " ";
//        }




        ///////////////////////
        //std::cout<<std::endl;
        int deleted = 0;
        for (unsigned long serve = 0; serve<pre_serve.size(); serve++){
            for (unsigned long pot=0; pot<shop_pots.size();pot++){
                if ((pre_serve[serve].order.noodle==shop_pots[pot].noodlename) && servenoodle(pre_serve[serve].index - deleted, pot)){
                    Serve temp;
                    temp.order_id = pre_serve[serve].order.id;
                    temp.pot_id = pot;
                    serving.push_back(temp);
                    deleted++;
                    break;
                }
            }
        }
       // std::cout<<"ServeAction()"<<std::endl;
        ServeAction* ret = new ServeAction (serving);
        return ret;
    }
        
    return new NoAction();
}

Noodle MyNoodleShop::Findnoodle(std::string name){
    for (unsigned long i=0;i<shop_noodles.size();i++){
        if (name.compare(shop_noodles[i].name)==0)
            return shop_noodles[i];
    }
    Noodle a;
    return a;
    
}

//returns the index of the noodle that's ready to be served
int MyNoodleShop::checknoodle(std::string name){
    for(unsigned long i = 0; i<shop_pots.size(); i++){
        if((shop_pots[i].noodlename == name)){
            return i;
        }
    }
    return -1;
}

bool MyNoodleShop::anycleanpots(){
    for (unsigned long i=0; i<shop_pots.size(); i++){
        // std::cout<<shop_pots[i].isClean<<std::endl;
        if (shop_pots[i].isClean)
            return true;
    }
    return false;
}

void MyNoodleShop::update_currorders(){
    for (unsigned long i=0; i<curr_orders.size();i++){
        curr_orders[i].time++;
        if (curr_orders[i].tip_left>0)
            curr_orders[i].tip_left-=10;
    }
}

void MyNoodleShop::update_pots(){
    for (unsigned long i=0; i<shop_pots.size();i++){
        if (!shop_pots[i].isClean){
            if (shop_pots[i].cooking_mins_left > 0){
                shop_pots[i].cooking_mins_left--;
            }
            else{
                if (shop_pots[i].time_until_stale > 0)
                    shop_pots[i].time_until_stale--;
               // std::cout<<shop_pots[i].noodlename<<" is ready"<<std::endl;
            }
        }
    }
}

int MyNoodleShop::cooknoodle(Noodle noodle) {
//find empty pot, assign noodle to empty pot, specify cooking minutes left, time until stale(30 min), servings left decrement, set isclean in empty pot to false
    for (unsigned long i=0; i<shop_pots.size(); i++){
        if (shop_pots[i].isClean){
            shop_pots[i].isClean = false;
            shop_pots[i].noodlename = noodle.name;
            shop_pots[i].cooking_mins_left=noodle.cook_time;
            shop_pots[i].time_until_stale = 30;
            shop_pots[i].servings_left=noodle.batch_size;
            return i;
        }
    }
    return -1;
}

bool MyNoodleShop::servenoodle(int order_index,int pot_id){
    //if servings left in pot(pot_id), delete order_id from curr_orders, decrement servings left by one, return true
    //else return false
    if (shop_pots[pot_id].servings_left>0){
        shop_pots[pot_id].servings_left--;
        curr_orders.erase(curr_orders.begin() + order_index);
        return true;
    }
    return false;
}

void MyNoodleShop::clean_pots(int pot_id) {
    shop_pots[pot_id].isClean = true;
    shop_pots[pot_id].noodlename = "";
    shop_pots[pot_id].cooking_mins_left = shop_pots[pot_id].time_until_stale = shop_pots[pot_id].servings_left = -1;
    // std::cout<<pot_id<<std::endl;
}

int MyNoodleShop::stale_empty(){
    for (unsigned long i=0; i<shop_pots.size(); i++){
        if (shop_pots[i].time_until_stale == 0 || shop_pots[i].servings_left == 0)
            return i;
    }
    return -1;
}

//return i if noodle with "noodlename" is currently being cooked in our pots
//return -1 otherwise
int MyNoodleShop::noodle_cooking(std::string noodlename){
    for(unsigned long i = 0; i<shop_pots.size(); i++){
        if((shop_pots[i].noodlename == noodlename) && (shop_pots[i].cooking_mins_left > 0)){
            return i;
        }
    }
    return -1;
}

int MyNoodleShop::noodle_cooked(std::string noodlename){
    for(unsigned long i = 0; i<shop_pots.size(); i++){
        if((shop_pots[i].noodlename == noodlename) && (shop_pots[i].cooking_mins_left == 0)){
            return i;
        }
    }
    return -1;
}
MyNoodleShop::~MyNoodleShop(){}

