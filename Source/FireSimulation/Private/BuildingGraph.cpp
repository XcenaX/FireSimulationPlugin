#include "BuildingGraph.h"

void UBuildingGraph::InitializeGraph()
{
    // Очистите текущий граф, если он уже был инициализирован
    Rooms.Empty();
    Doors.Empty();

    // Инициализация графа здесь
    // Например, создание начальных комнат и дверей, если они известны заранее
}

void UBuildingGraph::AddRoom(const FRoomNode& Room)
{
    // Добавьте новую комнату в список комнат
    Rooms.Add(Room);
}

void UBuildingGraph::AddDoor(const FDoorEdge& Door)
{
    // Добавьте новую дверь в список дверей
    Doors.Add(Door);

    // Обновите информацию о соседях для комнат, которые связаны данной дверью
    if (Rooms.IsValidIndex(Door.RoomAID) && Rooms.IsValidIndex(Door.RoomBID))
    {
        Rooms[Door.RoomAID].Neighbors.Add(Door.RoomBID);
        Rooms[Door.RoomBID].Neighbors.Add(Door.RoomAID);
    }
}

void UBuildingGraph::CalculateRoomAreas()
{
    // Здесь можно рассчитать площади комнат, если у вас есть необходимые данные
    // Это может потребовать дополнительных данных о геометрии комнат или других параметров
    for (FRoomNode& Room : Rooms)
    {
        // Пример расчета площади (заглушка)
        Room.Area = 100.0f; // Значение площади для примера
    }
}
