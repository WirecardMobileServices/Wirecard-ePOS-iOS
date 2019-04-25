Pod::Spec.new do |s|
  s.name                = "WDBrand"
  s.version             = "0.0.1"
  s.summary             = "Wirecard ePOS branding"
  s.description         = <<-DESC
    Wirecard ePOS branding framework
                       DESC
  s.homepage            = "https://wirecardmobileservices.github.io/Wirecard-ePOS-Developer/"
  s.license             = 'MIT'
  s.authors             = 'Radoslav Danko', 'Francisco Fortes', 'Marek Timko', 'Jaroslav Pulik'
  s.source              = { :git => "https://github.com/WirecardMobileServices/Wirecard-ePOS-iOS.git", :tag => s.version.to_s }
  s.platform            = :ios, '9.0'
  s.requires_arc        = true
  s.libraries           = 'c++', 'z.1', 'xml2'
  s.frameworks          = 'Foundation'

  s.vendored_frameworks = ['Pod/Classes/frameworks/WDBrand.framework']
  s.xcconfig            = { 'ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES' => 'YES' }

  s.dependency 'libextobjc/EXTScope', '~> 0.4'
end
