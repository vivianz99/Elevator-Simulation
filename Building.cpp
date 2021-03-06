#include <iostream>
#include "Building.h"
#include "Elevator.h"
#include "Passenger.h"
#include <vector>
#include <queue>
using namespace std;



Building::Building(int e_num, int f_num)
{
	elevators = e_num;
	floors = f_num;

	for (int i = 0; i <= elevators; i++) { //create i elevators and assign unique IDnumbers
		cout << "i= " << i << endl;
		Elevator my_elev(i);
		Elevator_vec.push_back(my_elev);
	}

	for (int i = 0; i < floors; i++) { //create i floors, put a queue of passengers in each floor
		queue <Passenger> PassengerQ;
		Floor_vec.push_back(PassengerQ);
	}
}

int Building::get_passengers()
{
	return passengers;
}

int Building::get_elevators()
{
	return elevators;
}

int Building::get_floors()
{
	return floors;
}


void Building::set_passengers(int p)
{
	passengers = p;
}

void Building::set_elevators(int e)
{
	elevators = e;
}

void Building::set_floors(int f)
{
	floors = f;
}



int Building::current_pass_in_ele()
{
	return entry_passengers - exit_passengers;
}

void Building::passenger_entry(int i)
{
	entry_passengers += i;
}

void Building::passenger_exit(int n)
{
	exit_passengers += n;
}

void Building::add_Passenger(Passenger the_passenger)
{

	for (int i = 1; i < Floor_vec.size() - 1; i++) {
		if (i == the_passenger.getCurrentFloor())
			Floor_vec[i].push(the_passenger);
	}

}

void Building::Decide()
{
	int d_floor = -1;
	for (int i = 0; i < Elevator_vec.size() - 1; i++) {
		if (!Elevator_vec[i].getIdel()) {
			cout << "elev.get.front.destin: " << Elevator_vec[i].getElevPass().front().getDestination() << endl;
			d_floor = Elevator_vec[i].elev_passengers.front().getDestination();

			if (d_floor > Elevator_vec[i].getCurrentFloor()) { //going up 
				for (int p = 0; p < Elevator_vec[i].elev_passengers.size(); p++) {
					if ((Elevator_vec[i].elev_passengers[p].getDestination() > Elevator_vec[i].getCurrentFloor()) && (Elevator_vec[i].elev_passengers[p].getDestination() < d_floor))
						d_floor = Elevator_vec[i].elev_passengers[p].getDestination();
				}
			}
			else if (d_floor < Elevator_vec[i].getCurrentFloor()) { //going down 
				for (int p = 0; p < Elevator_vec[i].elev_passengers.size(); p++) {
					if ((Elevator_vec[i].elev_passengers[p].getDestination() < Elevator_vec[i].getCurrentFloor()) && (Elevator_vec[i].elev_passengers[p].getDestination() > d_floor))
						d_floor = Elevator_vec[i].elev_passengers[p].getDestination();
				}
			}
		}
		Elevator_vec[i].setCurrentFloor(d_floor);
	}


}
void Building::loading_passengers() //looks at all the elevators in the building, it's current floor and if it needs to load any passengers
{
	Elevator elev;
	Passenger p;
	for (int e = 0; e < Elevator_vec.size() - 1; e++) {//for each elevator in the building
		for (int i = 0; i < Floor_vec.size() - 1; i++) { //for each floor's queue of passengers
			for (int q = 0; q < Floor_vec[i].size(); q++) { //for all the passengers in that queue
				if (p.getCurrentFloor() == elev.current_floor) //if that passenger is on that current floor
					elev.load(p); //load into elevator
			}
		}
	}
}
