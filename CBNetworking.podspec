Pod::Spec.new do |s|
  s.name         = "CBNetworking"
  s.version      =  "1.0.0"
  s.summary      = "对于AFNetWorking的封装."

  s.homepage     = "https://github.com/cbangchen/CBNetworking"
  s.license      = 'MIT'
  s.author       = { "陈超邦" => "http://cbang.info" }
  s.platform     = :ios, "7.0"
  s.ios.deployment_target = "7.0"
  s.source       = { :git => "https://github.com/cbangchen/CBNetworking.git", :tag => s.version }
  s.source_files  = 'CBNetworking/*.{h,m}'
  s.requires_arc = true
end
