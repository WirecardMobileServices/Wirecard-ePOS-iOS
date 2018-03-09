//
//  ReceiptVC.swift
//  eClear
//
//  Created by Danko, Radoslav on 16/12/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

import UIKit
import WebKit

@objc class ReceiptVC: UIViewController {

    var sale:WDSaleResponse? = nil
    let app:AppDelegate = UIApplication.shared.delegate as! AppDelegate
    
    @IBOutlet weak var webView: WKWebView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.navigationController?.setNavigationBarHidden(false, animated: true)
        self.generateReceipt()
    }

    func generateReceipt(){
        
        guard sale != nil else {
            self.navigationController?.popViewController(animated: true)
            app.showError("Receipt", text: "No Sale to generate the receipt from.")
            return
        }
        
        if let sale = sale {
            sale.receipt(true, showReturns: true, format: WDPrintFormat.HTML, dpi: WDPrintDpi.default, language:(UIApplication.shared.delegate as? AppDelegate)?.language ?? "en", completion: { ( receipts:[Any]?, error:Error?) in
                
                if error != nil{
                    self.navigationController?.popViewController(animated: true)
                    self.app.showError("Receipt", text: error?.localizedDescription)
                    return
                }
                
                if let receipts = receipts {
                    let arrReceipts:NSArray = receipts as NSArray
                    let html:NSString = arrReceipts.firstObject as! NSString
                    
                    if html.length > 0 {
                        let path = Bundle.main.bundlePath
                        let baseUrl = NSURL.fileURL(withPath: path)
                        
                        self.webView.loadHTMLString(html as String, baseURL: baseUrl)
                    }
                    else{
                        self.navigationController?.popViewController(animated: true)
                        self.app.showError("Receipt", text: "Failed to generate the HTML receipt.")

                    }
                    
                }
                else{
                    self.navigationController?.popViewController(animated: true)
                    self.app.showError("Receipt", text: "Failed to generate the receipt.")
                }
            })
        }
        
        
//        let webView = WKWebView(frame: CGRect(x:20,y:20,width:view.frame.size.width-40, height:view.frame.size.height-40))
//        webView.load(data, mimeType: "application/pdf", characterEncodingName:"", baseURL: pdfURL.deletingLastPathComponent())
//        view.addSubview(webView)
    }

}
