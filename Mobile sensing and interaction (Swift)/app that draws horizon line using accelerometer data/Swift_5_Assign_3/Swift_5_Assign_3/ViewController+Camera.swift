//
//  ViewController+Camera.swift
//  Swift_5_Assign_3
//
//  Created by David Grim on 5/12/21.
//

import Foundation
import AVFoundation
import UIKit

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
    
    // Takes A B and C calculated in the coremotion file and uses formula used in assignments description to calculate where the line is drawn
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        guard let cvBuffer = CMSampleBufferGetImageBuffer(sampleBuffer) else {
            return
        }
        let ciImage = CIImage(cvImageBuffer: cvBuffer)
        var uiImage = UIImage(ciImage: ciImage)
        print(uiImage.size)
        if showLine == true {
            uiImage = UIImage.drawLine(on: uiImage, from: CGPoint(x: -C/A , y: -C/B), to: CGPoint(x: -((1280 - 1) * B + C)/A, y: -((720 - 1) * A + C)/B), lineWidth: 8.0, color: UIColor.red.cgColor)
        }
        DispatchQueue.main.async {
            self.imageView.image = uiImage
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
}
