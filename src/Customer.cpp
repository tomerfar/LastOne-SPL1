#include "../include/Customer.h"
#include "../include/Order.h"
#include "../include/WareHouse.h"
#include <iostream>
//Constructor
Customer :: Customer(int id, const string &name, int locationDistance, int maxOrders):
id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders), ordersId(0) {}


//Methods
const std::string &Customer::getName() const {
  return name;
}

int Customer:: getId() const{
  return id;
}

int Customer:: getCustomerDistance() const{
  return locationDistance;
}

int Customer:: getMaxOrders() const{
  return maxOrders;
}

int Customer::  getNumOrders() const{
  return ordersId.size();
}
bool Customer:: canMakeOrder() const{
  if(maxOrders - ordersId.size() == 0){
    return false;
  }
  return true;
}

const vector<int> &Customer::getOrdersIds() const {
  return ordersId;
}

int Customer::addOrder(int orderId) { //return OrderId if order was added successfully, -1 otherwise
  if (static_cast<int>(ordersId.size()) < maxOrders) {
    ordersId.push_back(orderId);
    return orderId;
  }
  return -1;
} 

// Soldier Customer
SoldierCustomer::SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders)
  : Customer(id, name, locationDistance, maxOrders){}


SoldierCustomer *SoldierCustomer::clone() const {
  return new SoldierCustomer(*this);
}

// CivilianCustomer
CivilianCustomer::CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders)
  : Customer(id, name, locationDistance, maxOrders){}

CivilianCustomer *CivilianCustomer::clone() const {
  return new CivilianCustomer(*this);
}