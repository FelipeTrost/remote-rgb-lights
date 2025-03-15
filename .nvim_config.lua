-- Arduino stuff
ArduinoPort = "/dev/ttyUSB0"

local compile = "arduino-cli compile --fqbn esp32:esp32:nodemcu-32s rgb-lights/rgb-lights.ino;"
local upload = "arduino-cli upload -p " .. ArduinoPort .. " --fqbn esp32:esp32:nodemcu-32s rgb-lights/rgb-lights.ino;"
local cmd = compile .. upload

vim.keymap.set('n', '<leader>xc', ':wa | botright split | resize 15 | term ' .. cmd .. ' <CR>G',
  { noremap = true, silent = true })


-- Test stuff
local test_cmd = "cd testbuild; make; ./patterns_test"
vim.keymap.set('n', '<leader>xt', ':botright split | resize 15 | term ' .. test_cmd .. ' <CR>G',
  { noremap = true, silent = true })
