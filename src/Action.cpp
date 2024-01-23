#include "Action.h"
#include <iostream> 
using namespace std; //Solve the problem of the cout. Or we need to write the before our cout std::



ActionStatus BaseAction:: getStatus() const
{
    return status;
}

void BaseAction:: complete()
{
    status = ActionStatus::COMPLETED;
}

void BaseAction:: error(string errorMsg)
{
    status = ActionStatus:: ERROR;
    // update error message and print on screen: “Error: <error_msg>”
    // add later
}

string BaseAction:: getErrorMsg() const
{
    // add later לבדוק אם צריך להכניס פה תבניות של כל אפשרויות השגיאה האפשריות
}

SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}

 void SimulateStep:: act(WareHouse &wareHouse)
 {
    for(Order* order : wareHouse.getPendingOrders())
    {
        if(order->getStatus() == OrderStatus::PENDING)
        {
            for(Volunteer* vol : wareHouse.getVolunteers())
            {
                if(vol->canTakeOrder(*order))
                {
                    vol->acceptOrder(*order);
                }
            }
        }
         
        
    }
    
 }

 

AddOrder:: AddOrder(int id) : BaseAction(), customerId(id) {};

void AddOrder:: act(WareHouse &wareHouse)
{
    if (customerId > wareHouse.getCustomerCounter()) 
    {
        error("Cannot place this order. Customer does not exist.");  
        cout << getErrorMsg() << endl;
        //Add status errors
    }

    Customer &cus = wareHouse.getCustomer(customerId);

    if(cus.canMakeOrder())
    {
        Order *ord = new Order(wareHouse.getOrderCounter(), customerId, cus.getCustomerDistance()); 
        wareHouse.addOrder(ord);
        cus.addOrder(ord->getId());
        complete();
        // add status complete
    } 
    else {
        error("Cannot place this order. Customer has reached its order limit");
        cout << getErrorMsg() << endl;
        // add status error
    }
}



//---AddCustomer---------------------------------------------------------------------------------------
AddCustomer:: AddCustomer(string customerName, string customerType, int distance, int maxOrders): BaseAction(),
  customerName(customerName), distance(distance), maxOrders(maxOrders), customerType((customerType == "Soldier") ? CustomerType::Soldier : CustomerType::Civilian)
   {};
   // the ? operator checks to see if the customer type is Soldier or Civilian and gives the right type according to the string.

//Methods
void AddCustomer::act(WareHouse &wareHouse)
{
    int customerId = wareHouse.getCustomerCounter();
    if(this->customerType == CustomerType::Soldier)
    {
        SoldierCustomer newCustomer = SoldierCustomer(customerId, customerName, distance, maxOrders);
        wareHouse.addCustomer(&newCustomer);
    }
    else
    {
        CivilianCustomer newCustomer = CivilianCustomer(customerId, customerName, distance, maxOrders);
        wareHouse.addCustomer(&newCustomer);
    }
    
    complete();
    
}

string AddCustomer:: customerTypeToString(CustomerType type) //Convert the enum type to a string. check if neccesary
{
    switch (type) 
    {
    case CustomerType::Soldier:
        return "Soldier";
    case CustomerType::Civilian:
        return "Civilian";
    }
}

string AddCustomer:: toString() const
{
    cout << "customer " << this->customerName << this->customerType << this->distance << this->maxOrders << endl;
    // std_type = (*this).customerTypeToString(customerType);
    // return "Customer name: " + customerName + 
    // "\n"
    // + "Customer type: " + std_type + 
    // "\n"
    // + "distance " + to_string(distance) + 
    // "\n"
    // + "maxOrders " + to_string(maxOrders); 
    // ALL OF THIS NEEDS TO GO ON PRINT CUSTOMER STATUS!!!!
}

AddCustomer *AddCustomer:: clone() const
{
    return new AddCustomer(*this);
}


//---PrintStatusOrder--------------------------------------------------------------------------------------
 //Constructor
 PrintOrderStatus::PrintOrderStatus(int id):
 BaseAction(), orderId(id){};

 //Methods
 void PrintOrderStatus:: act(WareHouse& wareHouse)
 {
    Order &ord = wareHouse.getOrder(this->orderId); // getOrder returns a refernce to the order, which is why we create a refernce argument
    cout << ord.toString() << endl;
 }

 PrintOrderStatus *PrintOrderStatus:: clone() const
{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus:: toString() const
{
    string statusString = "orderStatus" + to_string(orderId) + ":";
    switch (getStatus())
    {
    case ActionStatus::COMPLETED:
        statusString += "COMPLETED";
        break;
    
    case ActionStatus::ERROR:
         statusString += "ERROR";
        break;
    }
    return statusString;
}
//---PrintStatusOrder--------------------------------------------------------------------------------------

//---PrintCustomerStatus-----------------------------------------------------------------------------------
//Constructors
PrintCustomerStatus::PrintCustomerStatus(int CustomerId):
BaseAction(), customerId(customerId){};

//Methods
void PrintCustomerStatus:: act(WareHouse &wareHouse)
{
    if (this->customerId > wareHouse.getCustomerCounter())
    {
        error("Customer doesn't exist.");
        cout << getErrorMsg() << endl; // לבדוק אם זה נכון  
    }
    else
    {
        Customer &cus = wareHouse.getCustomer(this->customerId);
        cout << "Customer Id: " << to_string(cus.getId()) << endl;
        for(int orderId : cus.getOrdersIds())
        {
            Order &ord = wareHouse.getOrder(orderId);
            cout << "OrderID: " << to_string(orderId) << endl;
            cout << "OrderStatus: " << ord.statusToString(ord.getStatus()) << endl;
        }
    }
}

PrintCustomerStatus *PrintCustomerStatus:: clone() const
{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus:: toString() const
{
    string customerString = "customerStatus" + to_string(this->customerId) + ":";
    switch (getStatus())
    {
    case ActionStatus::COMPLETED:
        customerString += "COMPLETED";
        break;
    
    case ActionStatus::ERROR:
    customerString += "ERROR";
        break;
    }
    return customerString;
}

//---PrintCustomerStatus-----------------------------------------------------------------------------------
//Constructors
 PrintVolunteerStatus::PrintVolunteerStatus(int id):
 BaseAction(), volunteerId(id){};

 //Methods
 void PrintVolunteerStatus:: act(WareHouse &wareHouse)
 {
    if(this->volunteerId > wareHouse.getVolunteerCounter())
    {
        error("volunteer doesn't exist.");
        cout << getErrorMsg() << endl; // לבדוק אם זה נכון 
    }
    else
    {
        Volunteer &vol = wareHouse.getVolunteer(volunteerId);
        // needs to see what type of volunteer is this and if he is limited or not, and print accordingly.
    }
 }

  PrintVolunteerStatus *PrintVolunteerStatus:: clone() const
  {
    return new PrintVolunteerStatus(*this);
  }

   string PrintVolunteerStatus:: toString() const
   {

   }
 
 









