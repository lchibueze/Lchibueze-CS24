#ifndef MYNOODLESHOP_H
#define MYNOODLESHOP_H

#include "NoodleShop.h"

class MyNoodleShop: public NoodleShop {
  // Member Variables
   /* int shop_type; //0 for simple.tsv, 1 for chef.special, 2 for lunch rush, 3 for custom_noodles, 4 for breakfast-lunch-dinner */
    
    int  mypots;      // The number of pots you have available.
    int  mrent;// The amount you paid to rent a stall for the day.
    int exp_cust;
    //int served_cust;
    
    struct Pot{
           bool isClean;
           std::string noodlename;
           int cooking_mins_left;
           int time_until_stale;
           int servings_left;
       };
       
       struct order_detail{
           Order order;
           int time;
           int tip_left;
       };
       struct serve_info{
           Order order;
           int index;
       };
    
    int pots_reserved;
    std::vector<int> pot_reserved_servings;
    std::vector<Pot> shop_pots;
    std::vector<Noodle> shop_noodles;    // Information about the noodles you're selling.
    std::vector<Noodle> future;
    //int money;
    
    std::vector<order_detail> curr_orders;
    
   
public:
  // Constructor
    MyNoodleShop(int npots, int rent, int customers, std::vector<Noodle> noodles);

  // Destructor?
    ~MyNoodleShop();

  // Required Member Functions
  std::vector<Order> orders(int minute, std::vector<Order> orderlist);
  Action* action(int minute);

    

  // Other Member Functions
    Noodle Findnoodle(std::string name);
    int potswithnoodle(std::string name);
    int checknoodle(std::string name);
    int findNoodleDemand(std::string);
    bool servenoodle(int order_index,int pot_id);
    void addFuture(std::vector<Noodle> future_vector);
    int anycleanpots();
    
    void update_currorders();
    
    void update_pots();
    
    void clean_pots(int pot_id);
    
    int cooknoodle(Noodle noodle);
    
    int stale_empty ();

    int noodle_cooking(std::string noodlename);
    int noodle_cooked(std::string noodlename);
};

#endif
