#include "ActionRepo.h"

void ActionAdd::executeUndo()
{
	repo.remove(addedCoat);
}

void ActionAdd::executeRedo()
{
	repo.add(addedCoat);
}

void ActionRemove::executeUndo()
{
	repo.add(removedCoat);
}

void ActionRemove::executeRedo()
{
	repo.remove(removedCoat);
}

void ActionUpdate::executeUndo()
{
	repo.updateAllFields(oldForm.getID(), oldForm.getSize(), oldForm.getColour(), oldForm.getPrice(), oldForm.getQuantity(), oldForm.getPhotograph());
}

void ActionUpdate::executeRedo()
{
	repo.updateAllFields(updatedForm.getID(), updatedForm.getSize(), updatedForm.getColour(), updatedForm.getPrice(), updatedForm.getQuantity(), updatedForm.getPhotograph());
}

Action::Action()
{
}
