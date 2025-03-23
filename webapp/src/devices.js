//@ts-check

// =================================================
// Discovery
// =================================================

/**
 * @param{string} ip
 * */
async function testIp(ip) {
  try {
    // key doesn't matter, we just want to see if we get a response
    const response = await fetch(new URL(`/randomkey/rgb/0/0/0`, ip));
    const json = response.json();
    if ("ok" in json) return ip;
  } catch { }
  return false;
}

// TODO: don't hardcode this??
export async function discoverDevices() {
  const base = "192.168.178.";
  /**  @type{Promise<string | false>[]} */
  const tests = [];

  for (let i = 0; i < 255; i++) {
    const ip = base + i.toString();
    tests.push(testIp(ip));
  }

  const results = await Promise.all(tests);
  /** @type{string[]} */
  const filteredResults = results.filter((r) =>
    typeof r === "boolean" ? false : true,
  );
  return filteredResults;
}

// =================================================
// Storage
// =================================================

/** @typedef{{version: string, storedDevices: string[], activeIndex: number}} Store */
const LOCAL_STORAGE_KEY = "arduino-rgb-leds";
const LOCAL_STORAGE_VERSION = "arduino-rgb-leds";

/** @returns{Store | undefined} */
export function getStore() {
  try {
    const storedItem = localStorage.getItem(LOCAL_STORAGE_KEY);
    if (!storedItem) return;
    const stored = JSON.parse(storedItem);

    if (stored.version !== LOCAL_STORAGE_VERSION) return undefined;
    return stored;
  } catch { }
}

/** @param {string} ip */
export function storeDevice(ip) {
  let store = getStore();
  if (!store) {
    store = {
      version: LOCAL_STORAGE_VERSION,
      storedDevices: [],
      activeIndex: -1,
    };
  }

  store.storedDevices.push(ip);

  localStorage.setItem(LOCAL_STORAGE_KEY, JSON.stringify(store));
}

/** @param {string} ip */
export function removeDevice(ip) {
  let store = getStore();
  if (!store) throw new Error("no devices stored");

  const index = store.storedDevices.findIndex((dip) => dip == ip);
  if (index === -1) throw new Error("device not found");

  store.storedDevices.splice(index, 1);
  store.activeIndex = Math.max(0, store.activeIndex - 1);

  localStorage.setItem(LOCAL_STORAGE_KEY, JSON.stringify(store));
}
