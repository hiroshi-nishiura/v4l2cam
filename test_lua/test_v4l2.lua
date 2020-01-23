#!/usr/bin/env lua

require 'v4l2cam_lua'
vcam = v4l2cam:new()

local t = get_table(nil)
print(t)

ui = require "tek.ui"
app = ui.Application:new()
win = ui.Window:new { Title = "test_v4l2_lua", HideOnEscape = true }

capture = ui.Area:new
{
   start = function(self)
      x,y,w,h = self:getRect()
      vcam:open(w,h)
      self.Window:addInputHandler(ui.MSG_INTERVAL, self, self.update)
   end,

   stop = function(self)
      vcam:close()
      self.Window:remInputHandler(ui.MSG_INTERVAL, self, self.update)
   end,

   update = function(self)
      local yuv = vcam:capture()
      if yuv then
         local rgb = vcam:yuv2rgb(yuv)
         print(rgb)
      end
      --self:setFlags(ui.FL_REDRAW)
   end,

   -- override draw 
   draw = function(self)
      local x,y,w,h = self:getRect()
      local screen = {}
      for y=0,h-1 do
         for x=0, w-1 do
            screen[w*y+x] = 0x000000ff
         end
      end
      self.Window.Drawable:drawRGB(x,y,screen,w,h,1,1)
      print('draw')
      return true
   end
}

-- Control Buttons
start = ui.Button:new {
   Text = "Start",
   onClick = function(self)
      capture:start()
   end
}

stop = ui.Button:new {
   Text = "Stop",
   onClick = function(self)
      capture:stop()
   end
}

quit = ui.Button:new {
   Text = "Quit",
   onClick = function(self)
      app:quit()
   end
}

-- Layouts
btns = ui.Group:new()
btns:addMember(start)
btns:addMember(stop)
btns:addMember(quit)

top = ui.Group:new { Orientation = "vertical" }
top:addMember(capture)
top:addMember(btns)

win:addMember(top)
app:addMember(win)
app:run()
