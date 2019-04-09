Pod::Spec.new do |s|
  s.name         = 'BPBLESDK-S02-iOS'
  s.version      = '0.0.1'
  s.license      = { :type => 'MIT'}
  s.homepage     = 'https://github.com/BodyPlusTechnology/BPBLESDK-S02-iOS'
  s.authors      = {'GrayLand119' => '441726442@qq.com'}
  s.summary      = 'A BLE SDK of Aerobic(Core S02)'
  s.platform     =  :ios, '9.0'
  s.source       =  { :git => 'https://github.com/BodyPlusTechnology/BPBLESDK-S02-iOS.git', :tag => '0.0.1' }
  s.source_files = 'FatArchitecture/BPBLESDK.framework/Headers/*.{h}'
  s.vendored_frameworks = 'FatArchitecture/BPBLESDK.framework'
  s.requires_arc = true
  s.swift_version = '4.2'
  s.dependency 'SSZipArchive'
  s.dependency 'iOSDFULibrary', '4.3.0'
end
