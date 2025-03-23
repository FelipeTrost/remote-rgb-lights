// Animation data
const ANIMATIONS = [
  { name: "Rainbow", icon: "fa-rainbow", color: "text-purple-500" },
  { name: "Fixed Color", icon: "fa-palette", color: "text-blue-500" },
  { name: "Chase", icon: "fa-bolt", color: "text-yellow-500" },
  {
    name: "Breathing",
    icon: "fa-compress-arrows-alt",
    color: "text-green-500",
  },
  { name: "Water Flow", icon: "fa-tint", color: "text-cyan-500" },
  { name: "Science", icon: "fa-flask", color: "text-indigo-500" },
  { name: "Rocket", icon: "fa-rocket", color: "text-red-500" },
  { name: "Starlight", icon: "fa-star", color: "text-yellow-300" },
  {
    name: "Triangle Wave",
    icon: "fa-wave-square",
    color: "text-pink-500",
  },
  { name: "Cloud", icon: "fa-cloud", color: "text-blue-300" },
  { name: "Polygon", icon: "fa-circle", color: "text-emerald-500" },
  { name: "Hexagon", icon: "fa-hexagon", color: "text-teal-500" },
  { name: "Pulse", icon: "fa-dot-circle", color: "text-orange-500" },
  { name: "Winter", icon: "fa-snowflake", color: "text-sky-300" },
  { name: "Fire", icon: "fa-fire", color: "text-red-600" },
  {
    name: "Sound Reactive",
    icon: "fa-microphone",
    color: "text-violet-500",
  },
];

// Render Animations
function renderAnimations() {
  const grid = document.getElementById("animationsGrid");
  grid.innerHTML = "";

  ANIMATIONS.forEach((animation) => {
    const div = document.createElement("div");
    div.className = `p-4 rounded-lg cursor-pointer transition-all duration-300 flex flex-col items-center space-y-2 bg-gray-800/50 hover:bg-gray-700/50`;
    div.innerHTML = `
                    <i class="fas ${animation.icon} w-6 h-6 ${animation.color}"></i>
                    <span class="text-white font-semibold text-center">${animation.name}</span>
                `;
    div.addEventListener("click", () => {
      // TODO: Implement LED strip animation logic
      console.log(`Selected animation: ${animation.name}`);
    });
    grid.appendChild(div);
  });
}

renderAnimations();

// =================================================
// Config Modal
// =================================================

/** @type{HTMLDialogElement}*/
const configDialog = document.getElementById("config-dialog");
const configButton = document.getElementById("configBtn");

configButton.addEventListener("click", () => configDialog.showModal());
configDialog.addEventListener("click", (event) => {
  const dialogDimensions = configDialog.getBoundingClientRect();
  if (
    event.clientX < dialogDimensions.left ||
    event.clientX > dialogDimensions.right ||
    event.clientY < dialogDimensions.top ||
    event.clientY > dialogDimensions.bottom
  ) {
    configDialog.close();
  }
});

function handleClickOutside(event) { }
