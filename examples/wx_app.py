#!/usr/bin/env python

import os
import sys
import threading
import numpy
import time

import IRT

import wx
import wx.glcanvas

from sample import Sample
import OpenGL.GL as GL

__version__ = "0.0.1"

class MainWindow(wx.Frame):
  def __init__(self, parent=None):
    wx.Frame.__init__(self, parent, -1, "wx IRT", wx.DefaultPosition, wx.DefaultSize, wx.DEFAULT_FRAME_STYLE)

    self.glWidget = IRTGLWidget(self, -1)

    controlPanel = wx.Panel(self, -1)
    box = wx.BoxSizer(wx.HORIZONTAL)
    box.Add(self.glWidget, 0, wx.CENTER)
    box.Add(controlPanel, 1, wx.EXPAND)
    self.SetSizer(box)

    self.statusBar = self.CreateStatusBar()

  def updateStatusFPS(self, fps):
    """
    Displays the FPS in the status bar
    """
    self.statusBar.SetStatusText("fps: %f" % fps)

class IRTGLWidget(wx.glcanvas.GLCanvas):
  """
  The OpenGL Widget that contains the IRT view
  """
  def __init__(self, parent, ID = -1):
    wx.glcanvas.GLCanvas.__init__(self, parent, ID)

    self.SetSize((640, 480))
    self.Bind(wx.EVT_PAINT, self.OnPaint)
    self.Bind(wx.EVT_SIZE, self.OnResize)
    self.thread = IRTThread(self, 640, 480, parent)
    self.thread.start()
    self.context = wx.glcanvas.GLContext(self)

  def OnResize(self, event):
    width, height = event.Size
    print "Resizing the scene (%d, %d)" % (width, height)
    self.thread.need_resize = (width, height)
    event.Skip()

  def OnPaint(self, event):
    dc = wx.PaintDC(self);
    self.SetCurrent(self.context)
    GL.glRasterPos(-1,-1)
    try:
      self.thread.lock.acquire()
      GL.glDrawPixels(self.thread.screen.shape[-2], self.thread.screen.shape[-1], GL.GL_RGB, GL.GL_FLOAT, self.thread.screen)
    finally:
      self.thread.lock.release()
    self.SwapBuffers()

class IRTThread(threading.Thread):
  def __init__(self, parent, width, height, mainWindow):
    threading.Thread.__init__(self)

    self.mainWindow = mainWindow
    self.glWidget = parent

    self.sample = Sample(width, height)
    self.sample.setRaytracer(IRT.Raytracer_Uniform)

    self.screens = [numpy.zeros((3, width, height), dtype = numpy.float32),numpy.zeros((3, width, height), dtype = numpy.float32)]
    self.lock = threading.Lock()
    self.currentScreen = 0

    self.pastFPS = []
    self.need_resize = False

  def resize(self, width, height):
    self.screens = [numpy.zeros((3, width, height), dtype = numpy.float32),numpy.zeros((3, width, height), dtype = numpy.float32)]
    self.sample.setResolution(width, height)

  def get_screen(self):
    return self.screens[self.currentScreen - 1]

  screen = property(get_screen)

  def paint(self):
    print "test"
    t = time.clock()
    self.sample(self.screens[self.currentScreen])
    t = time.clock() - t
    print "test"
    try:
      self.lock.acquire()
      self.currentScreen = 1 if self.currentScreen == 0 else 0
    finally:
      self.lock.release()
    self.pastFPS.append(t)
    if len(self.pastFPS) > 10:
      self.pastFPS = self.pastFPS[-10:]
    wx.CallAfter(self.mainWindow.updateStatusFPS, 10./sum(self.pastFPS))
    wx.CallAfter(self.glWidget.Refresh)

  def run(self):
    while True:
      self.paint()
      #if self.need_resize is not None:
        #self.resize(*self.need_resize)
        #self.need_resize = None

def main():
  app = wx.PySimpleApp()
  frm = MainWindow()
  frm.Show()
  app.MainLoop()

if __name__ == "__main__":
  main()
