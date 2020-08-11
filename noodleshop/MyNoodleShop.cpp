#include "MyNoodleShop.h"
#include <iostream>
#include <algorithm>
#include <map>

// This is here to avoid creating yet another object file.
NoodleShop* NoodleShop::create(int npots, int rent, int customers, std::vector<Noodle> noodles) {
  return new MyNoodleShop(npots,rent,customers,noodles);
}


//will be used to sort shop_noodles
bool getRatio(const Noodle &a, const Noodle &b)
{
    return (a.batch_size*a.serving_price/a.ingredient_cost) > (b.batch_size*b.serving_price/b.ingredient_cost);
    // return a.ingredient_cost < b.ingredient_cost;
}

bool sortOrders(const Order &a, const Order &b){
    return a.id < b.id;
}

// MyNoodleShop Member Functions
MyNoodleShop::MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles){
    mypots=npots;
    mrent=rent;
    shop_noodles = noodles;
    pots_reserved = 0;
    // looking through the 'orderlist', we will order the 'orderlist' from highest (servings*price/serving)/cost ratio.
    std::sort(shop_noodles.begin(), shop_noodles.end(), getRatio);
    exp_cust=customers;

    for (int i=0;i<npots; i++){
        //adds 0 to the reserved servings to the pot
        pot_reserved_servings.push_back(0);
        Pot temp;
        // below same as clean action
        temp.isClean = true;
        temp.noodlename = "";
        temp.cooking_mins_left = temp.time_until_stale = temp.servings_left = -1;
        shop_pots.push_back(temp);
    
    }
}

void MyNoodleShop::addFuture(std::vector<Noodle> future_vector){
    future = future_vector;
}

std::vector<Order> MyNoodleShop::orders(int minute, std::vector<Order> order_list) {
    update_currorders();
    update_pots();
    if (minute >=719){
        std::vector<Order> temp;
        return temp;
    }

    std::vector<Order> accepted_orders;
    
    //list the orders in 'order_list' from highest profit to lowest profit
    std::vector<Order> orderlist;
    for(unsigned long i = 0; i<shop_noodles.size(); i++){
        for(unsigned long j = 0; j<order_list.size(); j++){
            if(shop_noodles[i].name == order_list[j].noodle){
                orderlist.push_back(order_list[j]);
            }
        }
    }

    for (unsigned long i=0;i<orderlist.size();i++){
        //check to see if the noodle is ready to be served
        if ((checknoodle(orderlist[i].noodle)!=-1) && (shop_pots[checknoodle(orderlist[i].noodle)].servings_left - pot_reserved_servings[checknoodle(orderlist[i].noodle)] > 0) /*&& (findNoodleDemand(orderlist[i].noodle) < 16)*/){
            accepted_orders.push_back(orderlist[i]);
            pot_reserved_servings[checknoodle(orderlist[i].noodle)]++;
        }
        //if there are any clean pots (to cook noodles)
        else if (anycleanpots() - pots_reserved > 0){
            accepted_orders.push_back(orderlist[i]);
            pots_reserved++;
        }
    }

    std::sort(accepted_orders.begin(), accepted_orders.end(), sortOrders);

    for (unsigned long i=0;i<accepted_orders.size(); i++){
        order_detail temp;
        temp.order = accepted_orders[i];
        temp.time=0;
        temp.tip_left=100;
        curr_orders.push_back(temp);
    }

    return accepted_orders;
}

int MyNoodleShop::findNoodleDemand(std::string name){
    int counter = 0;
    for(unsigned long i = 0; i<curr_orders.size(); i++){
        if(curr_orders[i].order.noodle == name){
            counter++;
        }
    }
    return counter;
}

Action* MyNoodleShop::action(int minute){
//     if(minute%5 == 0){} //using this 

//     std::cout<<"curr_orders: {";
//     for(unsigned long i = 0; i<curr_orders.size(); i++){
//         std::cout<<curr_orders[i].order.id<< "."<<curr_orders[i].order.noodle<<" ";
//     }
//     std::cout<<"}"<<std::endl;
    

//     //START COOKING FIRST
//     if (anycleanpots() != 0) { /*we can't cook a noodle if it takes 10 minutes to cook if it is 8:25 depending on batch size*/
//         // check if the noodle we're cooking is already being cooked, if so, move on to next noodle. (if more orders coming in than orders being cooked, cook another batch)
//         for(unsigned long i = 0; i<curr_orders.size(); i++){
//             //if there aren't any noodles with order.noodle name being cooked, cook the noodle.
//             if(findNoodleDemand(curr_orders[i].order.noodle) > Findnoodle(curr_orders[i].order.noodle).batch_size || noodle_cooking(curr_orders[i].order.noodle) == -1){
//                 int pot_id = cooknoodle(Findnoodle(curr_orders[i].order.noodle));
//                 std::cout<<"CookAction("<<pot_id<<" "<<curr_orders[i].order.noodle<<")"<<std::endl;
//                 return new CookAction(pot_id,curr_orders[i].order.noodle);;
//             }
//         }
//     }

//     //CLEAN SECOND
//     int dirtypot = stale_empty();
//     if (dirtypot != -1){
//         clean_pots(dirtypot);
//         std::cout<<"CleanAction("<<dirtypot<<")"<<std::endl;
//         return new CleanAction(dirtypot);
//     }

//     //SERVE THIRD
//    // if (curr_orders.size()!=0)
//     std::vector<serve_info> pre_serve;
//     for (unsigned long i=0;i<curr_orders.size();i++){
//         int temp = noodle_cooked(curr_orders[i].order.noodle); //returns -1 if there arent any cooked noodles in the pots
//         if (temp != -1) {
//             if ((shop_pots[temp].time_until_stale>0) && (shop_pots[temp].cooking_mins_left==0) && (shop_pots[temp].servings_left>0)){
//                 serve_info a;
//                 a.order = curr_orders[i].order;
//                 a.index = i;
//                 pre_serve.push_back(a);
//             }
//         }
//     }
//     if (pre_serve.size()!=0){
//         std::vector<Serve> serving;
//         std::cout<<"pre_serve contains: ";
//         for(unsigned int i = 0; i<pre_serve.size(); i++){
//             std::cout<<pre_serve[i].order.noodle<< " ";
//         }

//         std::cout<<std::endl;
//         int deleted = 0;
//         for (unsigned long serve = 0; serve<pre_serve.size(); serve++){
//             for (unsigned long pot=0; pot<shop_pots.size();pot++){
//                 if ((pre_serve[serve].order.noodle==shop_pots[pot].noodlename) && servenoodle(pre_serve[serve].index - deleted, pot)){
//                     Serve temp;
//                     temp.order_id = pre_serve[serve].order.id;
//                     temp.pot_id = pot;
//                     serving.push_back(temp);
//                     deleted++;
//                     break;
//                 }
//             }
//         }
//         std::cout<<"ServeAction()"<<std::endl;
//         return new ServeAction(serving);
//     }

//     //LASTLY NO ACTION, have
//     std::cout<<"NoAction()"<<std::endl;
//     return new NoAction();


//try cleaning/cooking after every 5 mins
    if(minute%5 == 0){
    //     int dirtypot = stale_empty();
    //     if (dirtypot != -1){
    //         clean_pots(dirtypot);
    //         std::cout<<"CleanAction("<<dirtypot<<")"<<std::endl;
    //         CleanAction* temp = new CleanAction(dirtypot);
    //         return temp;
    //     }
    }

//    std::cout<<"curr_orders: {";
//    for(unsigned long i = 0; i<curr_orders.size(); i++){
//        std::cout<<curr_orders[i].order.id<< "."<<curr_orders[i].order.noodle<<" ";
//    }
//    std::cout<<"}"<<std::endl;

   // if (curr_orders.size()!=0)
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
        if (anycleanpots() != 0) { /*we can't cook a noodle if it takes 10 minutes to cook if it is 8:25 depending on batch size*/
            // check if the noodle we're cooking is already being cooked, if so, move on to next noodle. (if more orders coming in than orders being cooked, cook another batch)
            for(unsigned long i = 0; i<curr_orders.size(); i++){
                //if there aren't any noodles with order.noodle name being cooked, cook the noodle.
                if(noodle_cooking(curr_orders[i].order.noodle) == -1){
                    int pot_id = cooknoodle(Findnoodle(curr_orders[i].order.noodle));
                   std::cout<<"CookAction("<<pot_id<<" "<<curr_orders[i].order.noodle<<")"<<std::endl;
                    CookAction* temp = new CookAction(pot_id,curr_orders[i].order.noodle);
                    // std::cout<<curr_orders[0].order.noodle<<std::endl; for debugging
                    return temp;
                }
            }


            // for(unsigned long i = 0; i<shop_noodles.size(); i++){
            //     for(int j = 0; j<shop_noodles[i].cook_time; j++){
            //         if((minute+j < (int)(future.size())-1) && (shop_noodles[i].name == future[minute+j].name) && (potswithnoodle(shop_noodles[i].name)/((double)shop_pots.size()) <= 3.0/5.0)){
            //             int pot_id = cooknoodle(shop_noodles[i]);
            //             std::cout<<"CookAction("<<pot_id<<" "<<curr_orders[i].order.noodle<<")"<<std::endl;
            //             CookAction* temp = new CookAction(pot_id,curr_orders[i].order.noodle);
            //             // std::cout<<curr_orders[0].order.noodle<<std::endl; for debugging
            //             return temp;
            //         }
            //     }
            // }

            for(int j = 1; j<15; j++){
                if((minute+j < (int)(future.size())-1) && (potswithnoodle(future[minute+j].name)/((double)shop_pots.size()) <= 3.0/5.0) && ((future[minute+j].name).compare("NULL") != 0)){
                        int pot_id = cooknoodle(future[minute+j]);
                        std::cout<<"CookAction("<<pot_id<<" "<<future[minute+j].name<<")"<<std::endl;
                        CookAction* temp = new CookAction(pot_id,future[minute+j].name);
                        // std::cout<<curr_orders[0].order.noodle<<std::endl; for debugging
                        return temp;
                }
            }
        }
        int dirtypot = stale_empty();
        if (dirtypot != -1){
            clean_pots(dirtypot);
            std::cout<<"CleanAction("<<dirtypot<<")"<<std::endl;
            CleanAction* temp = new CleanAction(dirtypot);
            return temp;
        }
    }
    else {
        std::vector<Serve> serving;
        //std::cout<<"pre_serve contains: ";
        for(unsigned int i = 0; i<pre_serve.size(); i++){
          //  std::cout<<pre_serve[i].order.noodle<< " ";
        }




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
       std::cout<<"ServeAction()"<<std::endl;
        ServeAction* ret = new ServeAction (serving);
        return ret;
    }
    for(unsigned long i = 0; i<shop_noodles.size(); i++){
        for(int j = 0; j<shop_noodles[i].cook_time; j++){
            if((minute+j < (int)(future.size())-1) && (shop_noodles[i].name == future[minute+j].name) && (potswithnoodle(shop_noodles[i].name)/((double)shop_pots.size()) <= 3.0/5.0)){
                int pot_id = cooknoodle(shop_noodles[i]);
                std::cout<<"CookAction("<<pot_id<<" "<<curr_orders[i].order.noodle<<")"<<std::endl;
                CookAction* temp = new CookAction(pot_id,curr_orders[i].order.noodle);
                // std::cout<<curr_orders[0].order.noodle<<std::endl; for debugging
                return temp;
            }
        }
    }
    std::cout<<"NoAction()"<<std::endl;
    NoAction* temp = new NoAction();
    return temp;
}

Noodle MyNoodleShop::Findnoodle(std::string name){
    for (unsigned long i=0;i<shop_noodles.size();i++){
        if (name.compare(shop_noodles[i].name)==0)
            return shop_noodles[i];
    }
    Noodle a;
    return a;
    
}

//returns the index of the pot that has the noodle with 'name' in it
int MyNoodleShop::checknoodle(std::string name){
    for(unsigned long i = 0; i<shop_pots.size(); i++){
        if((shop_pots[i].noodlename == name)){
            return i;
        }
    }
    return -1;
}

//returns the number of clean pots
int MyNoodleShop::anycleanpots(){
    int counter = 0;
    for (unsigned long i=0; i<shop_pots.size(); i++){
        if (shop_pots[i].isClean)
            counter++;
    }
    return counter;
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
                std::cout<<shop_pots[i].noodlename<<" is ready"<<std::endl;
            }
        }
    }
}

int MyNoodleShop::cooknoodle(Noodle noodle) {
//find empty pot, assign noodle to empty pot, specify cooking minutes left, time until stale(30 min), servings left decrement, set isclean in empty pot to false
    for (unsigned long i=0; i<shop_pots.size(); i++){
        if (shop_pots[i].isClean){
            pots_reserved--;
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
        pot_reserved_servings[pot_id]--;
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

//return i if noodle with "noodlename" is cooked in our pots
//return -1 otherwise
int MyNoodleShop::noodle_cooked(std::string noodlename){
    for(unsigned long i = 0; i<shop_pots.size(); i++){
        if((shop_pots[i].noodlename == noodlename) && (shop_pots[i].cooking_mins_left == 0)){
            return i;
        }
    }
    return -1;
}

int MyNoodleShop::potswithnoodle(std::string name){
    int counter = 0;
    for(unsigned long i = 0; i<shop_pots.size(); i++){
        if(shop_pots[i].noodlename == name){
            counter++;
        }
    }
    return counter;
}

MyNoodleShop::~MyNoodleShop(){}
