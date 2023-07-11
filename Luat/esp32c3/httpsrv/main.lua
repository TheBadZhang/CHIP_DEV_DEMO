PROJECT = "uartdemo"
VERSION = "1.0.0"

-- һ��Ҫ���sys.lua !!!!
local sys = require "sys"
local uartid = 1

local LEDA = gpio.setup(12, 0)
local LED_D5 = gpio.setup(13, 0)
local state = 0
sys.taskInit(
    function()

		log.info("wlan", "wlan_init:", wlan.init())

		wlan.setMode(wlan.STATION)
		wlan.connect("laptop", "5872uy7a")   --�˺�������������Ϊ1ʱ�����Զ�����
		-- �ȴ�����·��,��ʱ��û��ȡ��ip
		result, _ = sys.waitUntil("WLAN_STA_CONNECTED")
		log.info("wlan", "WLAN_STA_CONNECTED", result)
		-- �ȵ��ɹ���ȡip�ʹ������Ͼ�������
		result, data = sys.waitUntil("IP_READY")
		log.info("wlan", "IP_READY", result, data)
        -- ntp.settz("CST-8")
        -- ntp.init("ntp.ntsc.ac.cn")
		-- result, _ = sys.waitUntil("NTP_SYNC_DONE")

		-- ����80�˿�
		httpsrv.start(80, function(client, method, uri, headers, body)
			-- method ���ַ���, ���� GET POST PUT DELETE
			-- uri Ҳ���ַ��� ���� / /api/abc
			-- headers table����
			-- body �ַ���
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
				�㿴�������վ��ʾ���оƬ��������
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
			-- ����ֵ��Լ�� code, headers, body
			-- ��û�з���ֵ, ��Ĭ�� 404, {} ,""
			return 404, {}, "Not Found" .. uri
		end)
		-- ���ھ�̬�ļ�
		-- ���1: / , ӳ��Ϊ /index.html
		-- ���2: /abc.html , �Ȳ��� /abc.html, �����ڵĻ����� /abc.html.gz
		-- ��gz����, ���Զ���ѹ���ļ�������Ӧ, ���󲿷������֧��.
		-- ��ǰĬ�ϲ��� /luadb/xxx �µ��ļ�,�ݲ�������
    end
)

-- �û������ѽ���---------------------------------------------
-- ��β������һ��
sys.run()
-- sys.run()֮����治Ҫ���κ����!!!!!

