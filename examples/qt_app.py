#!/usr/bin/env python

import os
import sys
import numpy
import time
import math

import IRT

try:
  from PySide.QtCore import *
  from PySide.QtGui import *
  from PySide.QtOpenGL import *
except:
  from PyQt4.QtCore import *
  from PyQt4.QtGui import *
  from PyQt4.QtOpenGL import *

import OpenGL.GL as GL
from sample import Sample

class MainWindow(QMainWindow):
  def __init__(self, parent=None):
    super(MainWindow, self).__init__(parent)

    bigWidget = QWidget()

    self.glWidget = IRTGLWidget(bigWidget, self)
    sidepanel = self.createSidePanel()

    layout = QHBoxLayout()
    layout.addWidget(self.glWidget, Qt.AlignHCenter | Qt.AlignVCenter)
    layout.addWidget(sidepanel, Qt.AlignHCenter | Qt.AlignVCenter)

    bigWidget.setLayout(layout)
    self.setCentralWidget(bigWidget)

    self.setWindowTitle(self.tr("Qt IRT"))
    self.statusFPS = QLabel()
    self.statusBar().addPermanentWidget(self.statusFPS)

    self.dirty = False

    self.connect(self, SIGNAL("updateFPS(double)"), self.updateStatusFPS)

  def updateStatusFPS(self, fps):
    """
    Displays the FPS in the status bar
    """
    self.statusFPS.setText("fps: %f" % fps)

  def rotateUp(self):
    """
    Rotates the raytracer in the up direction
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.rotateUp)

  def rotateDown(self):
    """
    Rotates the raytracer in the down direction
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.rotateDown)

  def rotateLeft(self):
    """
    Rotates the raytracer in the left direction
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.rotateLeft)

  def rotateRight(self):
    """
    Rotates the raytracer in the right direction
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.rotateRight)

  def goIn(self):
    """
    Go inside the screen
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.goIn)

  def goBack(self):
    """
    Go back outside the screen
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.goBack)

  def inclinateLeft(self):
    """
    Inclinates the raytracer in the left direction
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.inclinateLeft)

  def inclinateRight(self):
    """
    Inclinates the raytracer in the right direction
    """
    self.glWidget.thread.commands.append(self.glWidget.thread.inclinateRight)

  def setOversampling(self, oversampling):
    """
    Modifies the oversampling
    """
    self.glWidget.thread.commands.append(lambda : self.glWidget.thread.setOversampling(oversampling))

  def setLevels(self, levels):
    """
    Modifies the number of levels
    """
    self.glWidget.thread.commands.append(lambda : self.glWidget.thread.setLevels(levels))

  def createSidePanel(self):
    sidepanel = QFrame()
    layout_panel = QGridLayout(sidepanel)

    upbutton = QPushButton()
    upbutton.setText("^\n|")
    layout_panel.addWidget(upbutton, 0, 1)
    QObject.connect(upbutton, SIGNAL("clicked()"), self.rotateUp)

    downbutton = QPushButton()
    downbutton.setText("|\nv")
    layout_panel.addWidget(downbutton, 2, 1)
    QObject.connect(downbutton, SIGNAL("clicked()"), self.rotateDown)

    leftbutton = QPushButton()
    leftbutton.setText("<-")
    layout_panel.addWidget(leftbutton, 1, 0)
    QObject.connect(leftbutton, SIGNAL("clicked()"), self.rotateLeft)

    rightbutton = QPushButton()
    rightbutton.setText("->")
    layout_panel.addWidget(rightbutton, 1, 2)
    QObject.connect(rightbutton, SIGNAL("clicked()"), self.rotateRight)

    label = QLabel()
    label.setText("Rotation")
    layout_panel.addWidget(label, 1, 1, Qt.AlignJustify)

    mupbutton = QPushButton()
    mupbutton.setText("^\n|")
    layout_panel.addWidget(mupbutton, 3, 1)
    QObject.connect(mupbutton, SIGNAL("clicked()"), self.goIn)

    mdownbutton = QPushButton()
    mdownbutton.setText("|\nv")
    layout_panel.addWidget(mdownbutton, 5, 1)
    QObject.connect(mdownbutton, SIGNAL("clicked()"), self.goBack)

    ileftbutton = QPushButton()
    ileftbutton.setText("<--")
    layout_panel.addWidget(ileftbutton, 4, 0)
    QObject.connect(ileftbutton, SIGNAL("clicked()"), self.inclinateLeft)

    irightbutton = QPushButton()
    irightbutton.setText("-->")
    layout_panel.addWidget(irightbutton, 4, 2)
    QObject.connect(irightbutton, SIGNAL("clicked()"), self.inclinateRight)

    label = QLabel()
    label.setText("Move/Inclination")
    layout_panel.addWidget(label, 4, 1, Qt.AlignJustify)

    oversamplingbox = QSpinBox()
    oversamplingbox.setRange(1, 5)
    layout_panel.addWidget(oversamplingbox, 6, 1)
    QObject.connect(oversamplingbox, SIGNAL("valueChanged(int)"), self.setOversampling)
    oversamplingbox.setValue(2)

    levelbox = QSpinBox()
    levelbox.setRange(0, 5)
    layout_panel.addWidget(levelbox, 7, 1)
    QObject.connect(levelbox, SIGNAL("valueChanged(int)"), self.setLevels)
    levelbox.setValue(3)

    return sidepanel

class IRTGLWidget(QGLWidget):
  """
  The OpenGL Widget that contains the IRT view
  """
  def __init__(self, parent, mainWindow):
    #super(QGLWidget, self).__init__(parent)
    QGLWidget.__init__(self, parent)

    self.setFixedSize(800, 600)
    self.thread = IRTThread(self, 800, 600, mainWindow)
    QObject.connect(self, SIGNAL("updateView()"), self.updateGL)
    self.thread.start()

  def resizeGL(self, width, height):
    print "Resizing the scene (%d, %d)" % (width, height)
    self.setFixedSize(width, height)
    self.thread.emit(SIGNAL("resize()"), width, height)

  def paintGL(self):
    GL.glRasterPos(-1,-1)
    try:
      self.thread.lock.lockForRead()
      GL.glDrawPixels(self.thread.screen.shape[-2], self.thread.screen.shape[-1], GL.GL_RGB, GL.GL_FLOAT, self.thread.screen)
    finally:
      self.thread.lock.unlock()

class IRTThread(QThread):
  def __init__(self, parent, width, height, mainWindow):
    super(IRTThread, self).__init__(parent)

    self.mainWindow = mainWindow
    self.glWidget = parent

    self.sample = Sample(width, height)
    self.sample.setRaytracer(IRT.Raytracer_Halton_2_3)

    self.screens = [numpy.zeros((3, width, height), dtype = numpy.float32),numpy.zeros((3, width, height), dtype = numpy.float32)]
    self.lock = QReadWriteLock()
    self.currentScreen = 0

    self.pastFPS = []
    self.commands = []

    self.origin = self.sample.origin
    self.direction = self.sample.direction
    self.orientation = self.sample.orientation

    self.sample.raytracer.setViewer(self.origin, self.direction)
    self.sample.raytracer.setOrientation(self.orientation)

  def resize(self, width, height):
    self.screens = [numpy.zeros((3, width, height), dtype = numpy.float32),numpy.zeros((3, width, height), dtype = numpy.float32)]
    self.sample.setResolution(width, height)

  def get_screen(self):
    return self.screens[self.currentScreen - 1]

  screen = property(get_screen)

  def paint(self):
    t = time.time()
    self.sample(self.screens[self.currentScreen])
    t = time.time() - t
    try:
      self.lock.lockForWrite()
      self.currentScreen = 1 if self.currentScreen == 0 else 0
    finally:
      self.lock.unlock()
    self.pastFPS.append(t)
    if len(self.pastFPS) > 10:
      self.pastFPS = self.pastFPS[-10:]
    self.mainWindow.emit(SIGNAL("updateFPS(double)"), 10./sum(self.pastFPS))
    self.glWidget.emit(SIGNAL("updateView()"))

  def run(self):
    while True:
      self.paint()
      while self.commands:
        command = self.commands.pop()
        command()

  def rotateUp(self):
    """
    Rotates the raytracer in the up direction
    """
    self.orientation = rotate(self.orientation, numpy.cross(self.orientation, self.direction), -math.pi/180)
    self.direction = rotate(self.direction, numpy.cross(self.orientation, self.direction), -math.pi/180)
    self.sample.raytracer.setViewer(self.origin, self.direction)
    self.sample.raytracer.setOrientation(self.orientation)

  def rotateDown(self):
    """
    Rotates the raytracer in the down direction
    """
    self.orientation = rotate(self.orientation, numpy.cross(self.orientation, self.direction), math.pi/180)
    self.direction = rotate(self.direction, numpy.cross(self.orientation, self.direction), math.pi/180)
    self.sample.raytracer.setViewer(self.origin, self.direction)
    self.sample.raytracer.setOrientation(self.orientation)

  def rotateLeft(self):
    """
    Rotates the raytracer in the left direction
    """
    self.direction = rotate(self.direction, self.orientation, -math.pi/180)
    self.sample.raytracer.setViewer(self.origin, self.direction)

  def rotateRight(self):
    """
    Rotates the raytracer in the right direction
    """
    self.direction = rotate(self.direction, self.orientation, math.pi/180)
    self.sample.raytracer.setViewer(self.origin, self.direction)

  def goIn(self):
    """
    Goes inside the screen
    """
    self.origin += self.direction * .1
    self.sample.raytracer.setViewer(self.origin, self.direction)

  def goBack(self):
    """
    Goes back outside the screen
    """
    self.origin -= self.direction * .1
    self.sample.raytracer.setViewer(self.origin, self.direction)

  def inclinateLeft(self):
    """
    Rotates the raytracer in the left direction
    """
    self.orientation = rotate(self.orientation, self.direction, -math.pi/180)
    self.sample.raytracer.setOrientation(self.orientation)

  def inclinateRight(self):
    """
    Rotates the raytracer in the right direction
    """
    self.orientation = rotate(self.orientation, self.direction, math.pi/180)
    self.sample.raytracer.setOrientation(self.orientation)

  def setOversampling(self, oversampling):
    self.sample.raytracer.setOversampling(oversampling)

  def setLevels(self, levels):
    self.sample.raytracer.setLevels(levels)

def main():
  app = QApplication(sys.argv)
  app.setOrganizationName("Matthieu Brucher")
  app.setOrganizationDomain("matt.eifelle.com")
  app.setApplicationName("Qt IRT")
  form = MainWindow()
  form.show()
  app.exec_()

def rotate(vector, axis, angle):
  """
  Rotates a 3D vector with an axis and an angle
  """
  XY = math.sqrt(numpy.sum(axis[:2]**2))
  if XY == 0:
    cos_alpha = 1.
    sin_alpha = 0.
  else:
    cos_alpha = axis[0]/XY
    sin_alpha = axis[1]/XY

  axisb = numpy.array((XY, 0., axis[2]), dtype = numpy.float32)
  vectorb = numpy.array((vector[0] * cos_alpha + vector[1] * sin_alpha, -vector[0] * sin_alpha + vector[1] * cos_alpha, vector[2]), dtype = numpy.float32)

  XZ = math.sqrt(numpy.sum(axisb**2))
  if XZ == 0:
    cos_beta = 1.
    sin_beta = 0.
  else:
    sin_beta = axisb[0]/XZ
    cos_beta = axisb[2]/XZ

  vectorc = numpy.array((vectorb[0] * cos_beta + vectorb[2] * sin_beta, vectorb[1], -vectorb[0] * sin_beta + vectorb[2] * cos_beta), dtype = numpy.float32)

  cos_ = math.cos(angle)
  sin_ = math.sin(angle)
  vectorc = numpy.array((vectorc[0] * cos_ + vectorc[1] * sin_, -vectorc[0] * sin_ + vectorc[1] * cos_, vectorc[2]), dtype = numpy.float32)

  vectorb = numpy.array((vectorc[0] * cos_beta - vectorc[2] * sin_beta, vectorc[1], vectorc[0] * sin_beta + vectorc[2] * cos_beta), dtype = numpy.float32)

  vector = numpy.array((vectorb[0] * cos_alpha - vectorb[1] * sin_alpha, vectorb[0] * sin_alpha + vectorb[1] * cos_alpha, vectorb[2]), dtype = numpy.float32)
  return vector

if __name__ == "__main__":
  main()
