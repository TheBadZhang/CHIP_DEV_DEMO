PROJECT = "uartdemo"
VERSION = "1.0.0"

-- 一定要添加sys.lua !!!!
local sys = require "sys"
local uartid = 1

local LEDA = gpio.setup(12, 0)
local LED_D5 = gpio.setup(13, 0)
local state = 0
sys.taskInit(
    function()

		log.info("wlan", "wlan_init:", wlan.init())

		wlan.setMode(wlan.STATION)
		wlan.connect("laptop", "5872uy7a")   --此函数第三个参数为1时开启自动重连
		-- 等待连上路由,此时还没获取到ip
		result, _ = sys.waitUntil("WLAN_STA_CONNECTED")
		log.info("wlan", "WLAN_STA_CONNECTED", result)
		-- 等到成功获取ip就代表连上局域网了
		result, data = sys.waitUntil("IP_READY")
		log.info("wlan", "IP_READY", result, data)
        -- ntp.settz("CST-8")
        -- ntp.init("ntp.ntsc.ac.cn")
		-- result, _ = sys.waitUntil("NTP_SYNC_DONE")

		-- 监听80端口
		httpsrv.start(80, function(client, method, uri, headers, body)
			-- method 是字符串, 例如 GET POST PUT DELETE
			-- uri 也是字符串 例如 / /api/abc
			-- headers table类型
			-- body 字符串
			log.info("httpsrv", method, uri, json.encode(headers), body)
			if uri == "/led/1" then
				LEDA(1)
				state = 1
				return 200, {}, "ok"
			elseif uri == "/led/0" then
				LEDA(0)
				state = 0
				return 200, {}, "ok"
			elseif uri == "/led/toggle" then
				if state == 0 then
					LEDA(1)
					state = 1
				else
					LEDA(0)
					state = 0
				end
				return 200, {}, "ok"
			elseif uri == "/time" then
				return 200, {}, tostring(os.date())
			elseif uri == "/" then
				-- wlan.getIP()
				return 200, {}, [[<head>
				<h1>Hello World</h1>
				你看到这个网站表示这个芯片正常运行
				<script>
					function toggleLED() {
						const Http = new XMLHttpRequest();
						const url = 'http://]]..tostring(data)..[[/led/toggle';
						Http.open("GET", url);
						Http.send();
					}

					function offLED() {
						const Http = new XMLHttpRequest();
						const url = 'http://]]..tostring(data)..[[/led/0';
						Http.open("GET", url);
						Http.send();
					}

					function onLED() {
						const Http = new XMLHttpRequest();
						const url = 'http://]]..tostring(data)..[[/led/1';
						Http.open("GET", url);
						Http.send();
					}
				</script>
			</head>

			<body>
				<button onclick="offLED()">Turn Off LED</button>
				<button onclick="onLED()">Turn On LED</button>
				<button onclick="toggleLED()">Toggle LED</button>
			</body>]]
			end
			-- 返回值的约定 code, headers, body
			-- 若没有返回值, 则默认 404, {} ,""
			return 404, {}, "Not Found" .. uri
		end)
		-- 关于静态文件
		-- 情况1: / , 映射为 /index.html
		-- 情况2: /abc.html , 先查找 /abc.html, 不存在的话查找 /abc.html.gz
		-- 若gz存在, 会自动以压缩文件进行响应, 绝大部分浏览器支持.
		-- 当前默认查找 /luadb/xxx 下的文件,暂不可配置
    end
)

-- 用户代码已结束---------------------------------------------
-- 结尾总是这一句
sys.run()
-- sys.run()之后后面不要加任何语句!!!!!

