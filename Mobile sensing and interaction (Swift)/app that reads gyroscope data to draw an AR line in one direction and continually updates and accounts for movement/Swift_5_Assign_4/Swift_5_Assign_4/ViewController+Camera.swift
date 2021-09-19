//
//  ViewController+Camera.swift
//  Swift_5_Assign_3
//
//  Created by David Grim on 5/26/21.
//

import Foundation
import AVFoundation
import UIKit
import CoreMotion

extension ViewController{
    func setUpCamera(){
        captureSession = AVCaptureSession()
        captureSession.beginConfiguration()
        captureSession.sessionPreset = AVCaptureSession.Preset.hd1280x720
        
        let videoDevice = AVCaptureDevice.default(for: AVMediaType.video)
        guard let videoDeviceInput = try? AVCaptureDeviceInput(device: videoDevice!), self .captureSession.canAddInput(videoDeviceInput) else {
            print("something went wrong")
            return
        }
        self.captureSession.addInput(videoDeviceInput)
        self.setupOutput()
        self.captureSession.commitConfiguration()
    }
    
    
    func setupOutput(){
        let videoOutput = AVCaptureVideoDataOutput()
        videoOutput.alwaysDiscardsLateVideoFrames = true
        videoOutput.videoSettings = [kCVPixelBufferPixelFormatTypeKey as String: kCVPixelFormatType_32BGRA]
        videoOutput.setSampleBufferDelegate(self, queue: DispatchQueue.main)
        
        captureSession.addOutput(videoOutput)
        videoOutput.connections.first?.videoOrientation = .portrait
        
    }
    
    func startCamera(){
        if !captureSession.isRunning{
            captureSession.startRunning()
        }
    }
    
    func stopCamera(){
        captureSession.stopRunning()
    }
    
  
    func update_rotation(){
        //---matrix for alpha-----------
        let alphaMatrix = simd_double3x3(rows: [simd_double3(1,0,0),
                                                simd_double3(0,cos(self.alpha),-sin(self.alpha)),
                                                simd_double3(0,sin(self.alpha),cos(self.alpha))])
        
        
        //---matrix for beta----------
        let betaMatrix = simd_double3x3(rows: [simd_double3(cos(self.beta),0,-sin(self.beta)),
                                               simd_double3(0,1,0),
                                               simd_double3(sin(self.beta),0,cos(self.beta))])
        
        //---we will use this for calculating
        var rotMatrix = simd_double3x3(rows:                [simd_double3(self.attitudematrix.m11,self.attitudematrix.m12,self.attitudematrix.m13),
                                              simd_double3(self.attitudematrix.m21,self.attitudematrix.m22,self.attitudematrix.m23),
                                              simd_double3(self.attitudematrix.m31,self.attitudematrix.m32,self.attitudematrix.m33)])
        
        //-------calculate matrix using rodriguez formula--------
        var oof = self.rotationRate
        oof.x = self.rotationRate.x * (0.1)
        oof.y = self.rotationRate.y * (0.1)
        oof.z = self.rotationRate.z * (0.1)
            
        let I = simd_double3x3(rows: [simd_double3(1,0,0),
                                      simd_double3(0,1,0),
                                      simd_double3(0,0,1)])
            
        let skew = simd_double3x3(rows: [simd_double3(0,-oof.z,oof.y),
                                         simd_double3(oof.z,0,-oof.x),
                                         simd_double3(-oof.y,oof.x,0)])
        let x = oof.x * oof.x
        let y = oof.y * oof.y
        let z = oof.z * oof.z
            
        let mag = sqrt(x + y + z)
            
        let rod = (I - (skew * (sin(mag)/mag))) + ((skew * skew) * ((1 - cos(mag))/(mag * mag)))

        rotMatrix = rod
        //-------------------------------------------
        
        //check if the device is in gyro mode
        if sensorDevice == .ACCELEROMETER {
             if(self.count <= 1){
                 qc = rotMatrix * alphaMatrix * betaMatrix
             }
             else{
                qc = rotMatrix * qc
             }
         }
    }
    
    // Takes A B and C calculated in the coremotion file and uses formula used in assignments description to calculate where the line is drawn
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        guard let cvBuffer = CMSampleBufferGetImageBuffer(sampleBuffer) else {
            return
        }
        let ciImage = CIImage(cvImageBuffer: cvBuffer)
        var uiImage = UIImage(ciImage: ciImage)
        
        //------getting qc for device motion---------------------------
        
        if sensorDevice != .ACCELEROMETER{
            qc = simd_double3x3(rows: [simd_double3(self.attitudematrix.m11,self.attitudematrix.m12,self.attitudematrix.m13),
                                       simd_double3(self.attitudematrix.m21,self.attitudematrix.m22,self.attitudematrix.m23),
                                       simd_double3(self.attitudematrix.m31,self.attitudematrix.m32,self.attitudematrix.m33)])
        }
    
        //-----calculations for line points------------
        let alpha = -360/(480 * qc.columns.1.x + 360 * -qc.columns.1.z)
        let yStart = ((480 * alpha * -qc.columns.1.y)/(alpha * -qc.columns.1.z + 1)) + 1280/2
        
        let bleh = (480 * qc.columns.1.x - 719 * -qc.columns.1.z + -qc.columns.1.z * 360)
        let alpha2 = (719 - 360)/bleh
        let yEnd = ((480 * alpha2 * -qc.columns.1.y)/(alpha2 * -qc.columns.1.z + 1)) + 1280/2
        
    
        if showLine == true {
            uiImage = UIImage.drawLine(on: uiImage, from: CGPoint(x: 0, y: yStart), to: CGPoint(x:719,y:yEnd), lineWidth: 8.0, color: UIColor.red.cgColor)
        }
        DispatchQueue.main.async {
            self.imageView.image = uiImage
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
}
