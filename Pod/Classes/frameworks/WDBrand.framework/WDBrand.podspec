Pod::Spec.new do |s|
  s.name          = "WDBrand"
  s.version       = "0.0.1"
  s.summary       = "Wirecard ePOS branding"
  s.description   = <<-DESC
    Wirecard ePOS branding helper framework
                    DESC
  s.homepage      = "https://wirecardmobileservices.github.io/Wirecard-ePOS-Developer/"
  s.license       = { :type => 'Commercial', :file => 'LICENSE' }
  s.authors       = 'Radoslav Danko', 'Francisco Fortes', 'Marek Timko'
  s.source        = { :git => "https://p-ops-vcs.wirecard.sys/scm-webapp/git/acceptSDK-iOS/WDBrand" }
  s.platform      = :ios, '9.0'
  s.requires_arc  = true
  s.libraries     = 'c++', 'z.1', 'xml2'
  s.frameworks    = 'Foundation', 'UIKit'
  s.source_files  = '*.h', 'Style/**/*.{h,m,swift}'
  s.prefix_header_contents = '',
    '#import <WDBrand/WDBrand-Swift.h>',
    ''
  s.xcconfig      = { 'ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES' => 'YES' }
  s.dependency 'libextobjc/EXTScope', '~> 0.4'
end
