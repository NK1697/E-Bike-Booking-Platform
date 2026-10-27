// Mirrors the locations, roads, dock capacities, and starting bikes in src/SystemSetup.cpp.
const campusLocations = [
    { id: 1, name: "Aquamarine A", roads: [] },
    { id: 2, name: "Aquamarine B", roads: [] },
    { id: 3, name: "Mega Mess 1", roads: [] },
    { id: 4, name: "Mega Mess 2", roads: [] },
    { id: 5, name: "Garnet A", roads: [] },
    { id: 6, name: "Garnet B", roads: [] },
    { id: 7, name: "Hostel Office", roads: [] },
    { id: 8, name: "Logos Lecture Hall", roads: [] },
    { id: 9, name: "Orion", roads: [] },
    { id: 10, name: "MIG", roads: [] },
    { id: 11, name: "Main Gate", roads: [] },
    { id: 12, name: "NSO Ground", roads: [] },
    { id: 13, name: "Computer Lab", roads: [] },
    { id: 14, name: "2K Market", roads: [] },
    { id: 15, name: "Anjappar", roads: [] },
    { id: 16, name: "Library", roads: [] },
    { id: 17, name: "Computer Science Department", roads: [] },
    { id: 18, name: "Dominos", roads: [] }
];

const locationById = new Map(campusLocations.map((location) => [location.id, location]));
const campusRoads = [
    { from: 1, to: 2, distance: 1 }, { from: 1, to: 3, distance: 3 }, { from: 1, to: 15, distance: 8 },
    { from: 2, to: 3, distance: 3 }, { from: 2, to: 7, distance: 10 }, { from: 2, to: 15, distance: 8 },
    { from: 3, to: 4, distance: 4 }, { from: 3, to: 7, distance: 6 },
    { from: 4, to: 5, distance: 6 }, { from: 4, to: 7, distance: 7 },
    { from: 5, to: 6, distance: 1 }, { from: 5, to: 7, distance: 5 }, { from: 5, to: 8, distance: 4 },
    { from: 6, to: 7, distance: 5 }, { from: 6, to: 8, distance: 4 }, { from: 6, to: 9, distance: 6 },
    { from: 8, to: 9, distance: 7 }, { from: 8, to: 12, distance: 10 }, { from: 8, to: 13, distance: 2 },
    { from: 9, to: 10, distance: 1 }, { from: 10, to: 11, distance: 6 }, { from: 11, to: 12, distance: 4 },
    { from: 12, to: 14, distance: 6 }, { from: 12, to: 16, distance: 3 }, { from: 12, to: 18, distance: 12 },
    { from: 13, to: 14, distance: 7 }, { from: 14, to: 15, distance: 1 }, { from: 14, to: 17, distance: 4 },
    { from: 16, to: 17, distance: 4 }
];

campusRoads.forEach((road) => {
    locationById.get(road.from).roads.push({ to: road.to, distance: road.distance });
    locationById.get(road.to).roads.push({ to: road.from, distance: road.distance });
});

const dockSeeds = [
    { id: 101, locationId: 1, name: "Aquamarine A", bikes: 5, capacity: 8, firstBikeId: 501 },
    { id: 102, locationId: 2, name: "Aquamarine B", bikes: 5, capacity: 8, firstBikeId: 506 },
    { id: 103, locationId: 3, name: "Mega Mess 1", bikes: 5, capacity: 8, firstBikeId: 511 },
    { id: 104, locationId: 4, name: "Mega Mess 2", bikes: 5, capacity: 8, firstBikeId: 516 },
    { id: 105, locationId: 5, name: "Garnet A", bikes: 5, capacity: 8, firstBikeId: 521 },
    { id: 106, locationId: 6, name: "Garnet B", bikes: 5, capacity: 8, firstBikeId: 526 },
    { id: 107, locationId: 7, name: "Hostel Office", bikes: 10, capacity: 15, firstBikeId: 531 },
    { id: 108, locationId: 8, name: "Logos Lecture Hall", bikes: 15, capacity: 23, firstBikeId: 541 },
    { id: 109, locationId: 9, name: "Orion", bikes: 20, capacity: 30, firstBikeId: 556 },
    { id: 110, locationId: 10, name: "MIG", bikes: 5, capacity: 8, firstBikeId: 576 },
    { id: 111, locationId: 11, name: "Main Gate", bikes: 40, capacity: 60, firstBikeId: 581 },
    { id: 112, locationId: 12, name: "NSO Ground", bikes: 10, capacity: 15, firstBikeId: 621 },
    { id: 113, locationId: 13, name: "Computer Lab", bikes: 10, capacity: 15, firstBikeId: 631 },
    { id: 114, locationId: 14, name: "2K Market", bikes: 10, capacity: 15, firstBikeId: 641 },
    { id: 115, locationId: 15, name: "Anjappar", bikes: 5, capacity: 8, firstBikeId: 651 },
    { id: 116, locationId: 16, name: "Library", bikes: 25, capacity: 38, firstBikeId: 656 },
    { id: 117, locationId: 17, name: "Computer Science Department", bikes: 15, capacity: 23, firstBikeId: 681 },
    { id: 118, locationId: 18, name: "Dominos", bikes: 5, capacity: 8, firstBikeId: 696 }
];

const docks = dockSeeds.map((dock) => ({
    ...dock,
    availableBikeIds: Array.from({ length: dock.bikes }, (_, index) => dock.firstBikeId + index)
}));

let activeBike = null;
let currentLocation = null;
let afterLocationSaved = null;

const dockList = document.getElementById("dockList");
const notice = document.getElementById("notice");
const bikeCount = document.getElementById("bikeCount");
const dockCount = document.getElementById("dockCount");
const rideTitle = document.getElementById("rideTitle");
const rideText = document.getElementById("rideText");
const returnBtn = document.getElementById("returnBtn");
const locationLabel = document.getElementById("locationLabel");
const locationModal = document.getElementById("locationModal");
const locationInput = document.getElementById("locationInput");
const locationError = document.getElementById("locationError");
const returnModal = document.getElementById("returnModal");
const returnDockList = document.getElementById("returnDockList");

function getTravelTime(dock) {
    if (!currentLocation) return Infinity;
    if (currentLocation.id === dock.locationId) return 0;

    const distances = new Map(campusLocations.map((location) => [location.id, Infinity]));
    distances.set(currentLocation.id, 0);
    const unvisited = new Set(campusLocations.map((location) => location.id));

    while (unvisited.size) {
        let closestId = null;
        for (const locationId of unvisited) {
            if (closestId === null || distances.get(locationId) < distances.get(closestId)) {
                closestId = locationId;
            }
        }
        if (closestId === null || distances.get(closestId) === Infinity) break;
        if (closestId === dock.locationId) return distances.get(closestId);

        unvisited.delete(closestId);
        for (const road of locationById.get(closestId).roads) {
            const routeDistance = distances.get(closestId) + road.distance;
            if (routeDistance < distances.get(road.to)) distances.set(road.to, routeDistance);
        }
    }

    return distances.get(dock.locationId);
}

function locationDescription() {
    return currentLocation ? `${currentLocation.name} · ID ${currentLocation.id}` : "Set your location";
}

function updateLocationDisplay() {
    locationLabel.textContent = locationDescription();
}

function showLocationModal(nextAction) {
    afterLocationSaved = nextAction || null;
    locationError.textContent = "";
    locationInput.value = currentLocation ? currentLocation.id : "";
    locationModal.hidden = false;
    window.setTimeout(() => locationInput.focus(), 0);
}

function hideLocationModal() {
    locationModal.hidden = true;
    afterLocationSaved = null;
}

function requireLocation(nextAction) {
    if (!currentLocation) {
        showLocationModal(nextAction);
        return false;
    }
    nextAction();
    return true;
}

function showDocks() {
    dockList.innerHTML = "";
    let totalBikes = 0;
    const orderedDocks = currentLocation
        ? [...docks].sort((first, second) => getTravelTime(first) - getTravelTime(second))
        : [...docks];

    orderedDocks.forEach(function (dock) {
        totalBikes += dock.bikes;
        const tripTime = getTravelTime(dock);
        const isCurrentLocation = currentLocation && dock.locationId === currentLocation.id;
        const item = document.createElement("article");
        item.className = `dock-item${isCurrentLocation ? " current-dock" : ""}`;
        item.innerHTML = `
            <div class="dock-top">
                <div>
                    <div class="dock-heading">
                        <h3 class="dock-name">${dock.name}</h3>
                        ${isCurrentLocation ? '<span class="here-tag">You are here</span>' : ""}
                    </div>
                    <span class="dock-distance">${currentLocation ? (tripTime === 0 ? "At your location" : `${tripTime} min away`) : "Set your location to calculate distance"} · Dock ${dock.id}</span>
                </div>
                <span class="bike-tag">${dock.bikes} bike${dock.bikes === 1 ? "" : "s"}</span>
            </div>
            <div class="dock-bottom">
                <span>${dock.capacity - dock.bikes} open return space${dock.capacity - dock.bikes === 1 ? "" : "s"}</span>
                <button class="rent-btn" ${dock.bikes === 0 || activeBike ? "disabled" : ""}>${activeBike ? "Ride in progress" : "Rent bike"}</button>
            </div>`;

        item.querySelector("button").addEventListener("click", function () {
            requireLocation(() => rentBike(dock));
        });
        dockList.appendChild(item);
    });

    bikeCount.textContent = totalBikes;
    dockCount.textContent = docks.length;
}

function rentBike(dock) {
    if (dock.bikes === 0 || activeBike || !currentLocation) return;
    const bikeId = dock.availableBikeIds.pop();
    if (bikeId === undefined) return;
    dock.bikes--;
    activeBike = { pickupDock: dock, id: bikeId };
    rideTitle.textContent = `Bike ${activeBike.id} is active`;
    rideText.textContent = `Picked up at ${dock.name}. Choose any dock with space when you return.`;
    returnBtn.disabled = false;
    notice.textContent = `Bike ${activeBike.id} is unlocked. Your closest pickup was ${dock.name}.`;
    showDocks();
}

function showReturnModal() {
    if (!activeBike) return;
    document.getElementById("returnBikeId").textContent = activeBike.id;
    returnDockList.innerHTML = "";
    const orderedDocks = [...docks].sort((first, second) => getTravelTime(first) - getTravelTime(second));

    orderedDocks.forEach(function (dock) {
        const spaces = dock.capacity - dock.bikes;
        const item = document.createElement("article");
        item.className = "return-dock-option";
        item.innerHTML = `
            <div>
                <strong>${dock.name}</strong>
                <span>Dock ${dock.id} · ${getTravelTime(dock) === 0 ? "At your location" : `${getTravelTime(dock)} min away`} · ${spaces} space${spaces === 1 ? "" : "s"} open</span>
            </div>
            <button class="select-dock-btn" ${spaces === 0 ? "disabled" : ""}>${spaces === 0 ? "Full" : "Return here"}</button>`;
        item.querySelector("button").addEventListener("click", function () {
            returnBike(dock);
        });
        returnDockList.appendChild(item);
    });
    returnModal.hidden = false;
}

function hideReturnModal() {
    returnModal.hidden = true;
}

function returnBike(returnDock) {
    if (!activeBike || returnDock.bikes >= returnDock.capacity) return;
    const bikeId = activeBike.id;
    returnDock.bikes++;
    returnDock.availableBikeIds.push(bikeId);
    currentLocation = locationById.get(returnDock.locationId);
    updateLocationDisplay();
    activeBike = null;
    rideTitle.textContent = "No active ride";
    rideText.textContent = "Ready for your next trip. Browse bikes near your current location.";
    returnBtn.disabled = true;
    notice.textContent = `Bike ${bikeId} returned successfully to ${returnDock.name}.`;
    hideReturnModal();
    showDocks();
}

document.getElementById("locationBtn").addEventListener("click", function () {
    showLocationModal();
});

document.getElementById("findBtn").addEventListener("click", function () {
    requireLocation(function () {
        document.querySelector(".dock-section").scrollIntoView({ behavior: "smooth", block: "start" });
        notice.textContent = `Docks are sorted from ${currentLocation.name}.`;
        showDocks();
    });
});

returnBtn.addEventListener("click", function () {
    requireLocation(showReturnModal);
});

document.getElementById("locationForm").addEventListener("submit", function (event) {
    event.preventDefault();
    const locationId = Number(locationInput.value.trim());
    const selectedLocation = locationById.get(locationId);

    if (!selectedLocation) {
        locationError.textContent = "Enter a valid campus location ID from 1 to 5.";
        locationInput.focus();
        return;
    }

    currentLocation = selectedLocation;
    updateLocationDisplay();
    notice.textContent = `Location saved: ${currentLocation.name}. Docks are now sorted by travel time.`;
    locationModal.hidden = true;
    const nextAction = afterLocationSaved;
    afterLocationSaved = null;
    showDocks();
    if (nextAction) nextAction();
});

document.getElementById("closeLocationModal").addEventListener("click", hideLocationModal);
document.getElementById("closeReturnModal").addEventListener("click", hideReturnModal);

[locationModal, returnModal].forEach(function (modal) {
    modal.addEventListener("click", function (event) {
        if (event.target === modal) modal.hidden = true;
    });
});

document.addEventListener("keydown", function (event) {
    if (event.key !== "Escape") return;
    hideLocationModal();
    hideReturnModal();
});

updateLocationDisplay();
showDocks();
