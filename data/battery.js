const batteryLevel = document.getElementById("battery-level");
const batteryPercentText = document.getElementById("battery-percent");
const batteryVoltageText = document.getElementById("battery-voltage");

async function requestBattery() {
  const response = await fetch("/battery", { cache: "no-store" });
  if (!response.ok) throw new Error("Battery request failed");
  return response.json();
}

export async function syncBattery() {
  const { voltage, percent } = await requestBattery();
  const clampedPercent = Math.max(0, Math.min(100, Number(percent)));
  const roundedVoltage = Number(voltage).toFixed(2);
  batteryLevel.style.width = `${clampedPercent}%`;
  batteryPercentText.textContent = `${Math.round(clampedPercent)}%`;
  batteryVoltageText.textContent = `${roundedVoltage} V`;
}
