//
//  UIImage+Rendering.swift
//  Swift_5_Assign_4
//
//  Created by renpeng on 2021/5/15.
//

import UIKit
import Foundation
import AVFoundation

extension UIImage{
    /*
     * Draw a line, given two endpoints, on an UIImage
     */
    static func drawLine(on image: UIImage, from startPoint: CGPoint, to endPoint: CGPoint, lineWidth: CGFloat, color: CGColor) -> UIImage {
        // Create an image context from UIImage
        // Creates a bitmap-based graphics context and makes it the current context.
        UIGraphicsBeginImageContext(image.size)
        image.draw(at: CGPoint.zero)
        // Returns the current graphics context.
        guard let context = UIGraphicsGetCurrentContext() else { return UIImage() }
        
        // Draw a line on an image
        context.setLineWidth(lineWidth)
        context.setStrokeColor(color)
        context.move(to: startPoint)
        context.addLine(to: endPoint)
        // Paints a line along the current path.
        context.strokePath()
        
        // Return an image with a drawn line
        // Returns an image from the contents of the current bitmap-based graphics context.
        guard let resultImage = UIGraphicsGetImageFromCurrentImageContext() else { return UIImage() }
        // Removes the current bitmap-based graphics context from the top of the stack.
        UIGraphicsEndImageContext()
        return resultImage
    }
}

