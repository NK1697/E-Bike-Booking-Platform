const docks = [
    { id: 101, name: "Library", distance: 3, bikes: 2 },
    { id: 102, name: "Hostel Zone", distance: 7, bikes: 1 }
];

let activeBike = null;

const dockList = document.getElementById("dockList");
const notice = document.getElementById("notice");
const bikeCount = document.getElementById("bikeCount");
const rideTitle = document.getElementById("rideTitle");
const rideText = document.getElementById("rideText");
const returnBtn = document.getElementById("returnBtn");

function showDocks() {
    dockList.innerHTML = "";
    let totalBikes = 0;

    docks.forEach(function (dock) {
        totalBikes += dock.bikes;
        const item = document.createElement("article");
        item.className = "dock-item";
        item.innerHTML = `
            <div class="dock-top">
                <div>
                    <h3 class="dock-name">${dock.name}</h3>
                    <span class="dock-distance">${dock.distance} min away · Dock ${dock.id}</span>
                </div>
                <span class="bike-tag">${dock.bikes} bike${dock.bikes === 1 ? "" : "s"}</span>
            </div>
            <div class="dock-bottom">
                <span>Simple campus pickup point</span>
                <button class="rent-btn" ${dock.bikes === 0 || activeBike ? "disabled" : ""}>Rent bike</button>
            </div>`;

        const rentBtn = item.querySelector("button");
        rentBtn.addEventListener("click", function () { rentBike(dock); });
        dockList.appendChild(item);
    });

    bikeCount.textContent = totalBikes;
}

function rentBike(dock) {
    if (dock.bikes === 0 || activeBike) return;
    dock.bikes--;
    activeBike = { dock: dock, id: dock.id === 101 ? 501 : 503 };
    rideTitle.textContent = "Bike " + activeBike.id + " is active";
    rideText.textContent = "Started from " + dock.name + ". Return it to any campus dock.";
    returnBtn.disabled = false;
    notice.textContent = "Your bike is ready. Have a safe ride!";
    showDocks();
}

function returnBike() {
    if (!activeBike) return;
    activeBike.dock.bikes++;
    notice.textContent = "Bike returned successfully to " + activeBike.dock.name + ".";
    activeBike = null;
    rideTitle.textContent = "No active ride";
    rideText.textContent = "Rent a bike from a campus dock to get started.";
    returnBtn.disabled = true;
    showDocks();
}

document.getElementById("findBtn").addEventListener("click", function () {
    document.querySelector(".dock-section").scrollIntoView({ behavior: "smooth" });
});

returnBtn.addEventListener("click", returnBike);
showDocks();
