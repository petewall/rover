const colorPicker = document.getElementById("color-picker");

const clampColor = (value) => Math.max(0, Math.min(255, Number(value) || 0));

const rgbToHex = (r, g, b) =>
  `#${[r, g, b].map((component) => component.toString(16).padStart(2, "0")).join("")}`;

const hexToRgb = (hex) => {
  const sanitized = hex.replace("#", "");
  if (sanitized.length !== 6) {
    return { r: 0, g: 0, b: 0 };
  }
  return {
    r: clampColor(parseInt(sanitized.substring(0, 2), 16)),
    g: clampColor(parseInt(sanitized.substring(2, 4), 16)),
    b: clampColor(parseInt(sanitized.substring(4, 6), 16)),
  };
};

async function requestColor(color) {
  let query = "";
  if (color) {
    const { r, g, b } = color;
    query = `?r=${clampColor(r)}&g=${clampColor(g)}&b=${clampColor(b)}`;
  }

  const response = await fetch(`/led${query}`, { cache: "no-store" });
  if (!response.ok) {
    throw new Error("Request failed");
  }
  const payload = await response.json();
  return {
    r: clampColor(payload.r ?? 0),
    g: clampColor(payload.g ?? 0),
    b: clampColor(payload.b ?? 0),
  };
}

export async function syncColor() {
  const { r, g, b } = await requestColor();
  colorPicker.value = rgbToHex(r, g, b);
}

colorPicker.addEventListener("input", (event) => {
  const { r, g, b } = hexToRgb(event.target.value);
  requestColor({ r, g, b }).catch((error) => {
    console.error("Failed to update LED color", error);
    alert("Unable to reach rover LED controller.");
    syncColor().catch((err) => console.error("Resync failed", err));
  });
});
