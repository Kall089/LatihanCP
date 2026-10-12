const materials = ["HTML", "CSS"];
const form = document.querySelector("#material-form");
const input = document.querySelector("#material");
const list = document.querySelector("#material-list");

function render() {
  list.replaceChildren(...materials.map((material, index) => {
    const item = document.createElement("li");
    const label = document.createElement("span");
    const button = document.createElement("button");
    label.textContent = material;
    button.type = "button";
    button.textContent = "Hapus";
    button.dataset.index = index;
    item.append(label, " ", button);
    return item;
  }));
}

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const material = input.value.trim();
  if (!material) return;
  materials.push(material);
  form.reset();
  render();
});

list.addEventListener("click", (event) => {
  const button = event.target.closest("button[data-index]");
  if (!button) return;
  materials.splice(Number(button.dataset.index), 1);
  render();
});

render();
