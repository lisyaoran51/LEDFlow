#include "LightController.h"

LightController::LightController(ShiftRegisterController* sReg, PitchToKeyboardConverter* cnvr) {
	shiftReg = sReg;
	converter = cnvr;
	lightStatus = new LinkedList<Pair>();
	ledStatus = new LinkedList<Pair>();
}

void LightController::Run() {
	shiftReg->Run();
}

void LightController::Update(LinkedList<Pair>* lStatus) {
	
	//if (lightStatus->Compare(lStatus)) return;
	if (compare(lStatus))
		return;
		
	update(lStatus);
	converter->Convert(lStatus, ledStatus);
	shiftReg->Set(ledStatus);
}

bool LightController::compare(LinkedList<Pair>* lStatus) 
{
	if (lStatus->size() != lightStatus->size())
		return false;

	/*
	bool judges[lStatus->size()];
	for (int i = 0; i < lStatus->size(); i++) {
		judges[i] = false;
	}
	
	for (int i = 0; i < lStatus->size(); i++) {
		for (int j = 0; j < lStatus->size(); j++) {
			if (lStatus->get(i) == lightStatus->get(j)) {
				
				if (!judges[j])
					judges[j] = true;
				else
					continue;	// if two status are the same, the judges[j] should've been assigned true previously. So skip judges[j].
				
				break;
			}
		}
	}

	for (int i = 0; i < lStatus->size(); i++) {
		if (!judges[i])
			return false;
	}
	return true;
	*/

	for (int i = 0; i < lStatus->size(); i++) {
		if (lStatus->get(i).first != lightStatus->get(i).first || lStatus->get(i).second != lightStatus->get(i).second) {
			return false;
		}
	}
	return true;
}

void LightController::update(LinkedList<Pair>* lStatus) 
{
	lightStatus->clear();

	for (int i = 0; i < lStatus->size(); i++) {
		lightStatus->add(lStatus->get(i));
	}
}
