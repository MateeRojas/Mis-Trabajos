TestCase subclass: #AlgoPedidosTests	instanceVariableNames: ''	classVariableNames: ''	package: 'TP1-Tests'!!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 20:11'!test09RemoverProductosAPedido
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoConDeliveryPara: 'Sebas'.
	
	algoPedidos agregarProductoConNombre: 'Asado' precio: 500.0 yCantidad: 1 para: 'Sebas'.
	algoPedidos agregarMenuConNombre: 'Men√∫ Lunes' precio: 200.0 yCantidad: 1 para: 'Sebas'.
	algoPedidos agregarProductoConNombre: 'vino' precio: 250.0 yCantidad: 1 para: 'Sebas'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Sebas') equals: (950*1.2). "20% extra"
	
	algoPedidos removerProductoConNombre: 'vino' para: 'Sebas'.
	algoPedidos removerMenuConNombre: 'Men√∫ Lunes' para: 'Sebas'.
	
	self assert: (algoPedidos precioPedidoDe: 'Sebas') equals: (500*1.2). "20% extra"! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 19:17'!test02SeAgreganProductosAPedidoConDelivery
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoConDeliveryPara: 'Santiago'.
	
	algoPedidos agregarProductoConNombre: 'Asado' precio: 500.0 yCantidad: 1 para: 'Santiago'.
	algoPedidos agregarProductoConNombre: 'vino' precio: 250.0 yCantidad: 1 para: 'Santiago'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Santiago') equals: (750*1.2). "20% extra"! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 20:10'!test05SeCambiaCantidadDeProductosEnPedido
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Carlos'.
	
	algoPedidos agregarMenuConNombre: 'Men√∫ viernes' precio: 200.0 yCantidad: 1 para: 'Carlos'.
	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Carlos'.
	
	self assert: (algoPedidos cantidadProductosEnPedidoDe: 'Carlos') equals: 2.
	
	algoPedidos actualizarProductoConNombre: 'Gaseosa' conCantidad: 3 para: 'Carlos'.
	
	self assert: (algoPedidos cantidadProductosEnPedidoDe: 'Carlos') equals: 4.! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 19:05'!test04AplicarCuponDeDescuentoPorcentualAPedidoConProductos
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Tom√°s'.
	
	algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 1 para: 'Tom√°s'.
	algoPedidos agregarCuponAPedidoDe: 'Tom√°s' conPorcentaje: 10. 
	
	self assert: (algoPedidos precioPedidoDe: 'Tom√°s') closeTo: (200*0.9) precision: 0.01. "-10%"! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 20:11'!test07AgregarCuponAPedidoConMenuNoRealizaDescuento
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Julian'.

	algoPedidos agregarMenuConNombre: 'Menu jueves' precio: 200.0 yCantidad: 1 para: 'Julian'.
	algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 2 para: 'Julian'.

	algoPedidos agregarCuponAPedidoDe: 'Julian' conValor: 15.
	
	self assert: (algoPedidos precioPedidoDe: 'Julian') equals: 600.0.! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Mateo 11/2/2020 23:14'!test03SeAgregaMenuAPedido
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Pablo'.
	
	algoPedidos agregarMenuConNombre: 'Menu viernes' precio: 200.0 yCantidad: 1 para: 'Pablo'.
	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Pablo'.
	
	self assert: (algoPedidos precioPedidoDe: 'Pablo') closeTo: 450.0 precision: 0.1.! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 20:11'!test08RemoverCuponDeDescuentoAPedido
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Martin'.

	algoPedidos agregarCuponAPedidoDe: 'Martin' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Martin'.
	
	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 335.0 precision: 0.01.  "-15"
	
	algoPedidos removerCuponDePedidoDe: 'Martin'.

	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 350.0 precision: 0.01.! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 19:17'!test01SeAgreganProductosAPedidoParaRetirar
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Eugenio'.
	
	algoPedidos agregarProductoConNombre: 'Milanesa' precio: 250.0 yCantidad: 2 para: 'Eugenio'.
	algoPedidos agregarProductoConNombre: 'Gelatina' precio: 100.0 yCantidad: 1 para: 'Eugenio'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Eugenio') equals: 600.0.! !!AlgoPedidosTests methodsFor: 'tests' stamp: 'Edson 10/20/2020 20:11'!test06AplicarCuponDeDescuentoFijoAPedidoConProductos
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Diego'.

	algoPedidos agregarCuponAPedidoDe: 'Diego' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Milanesa' precio: 350.0 yCantidad: 1 para: 'Diego'.
	
	self assert: (algoPedidos precioPedidoDe: 'Diego') closeTo: 335.0 precision: 0.01. "-15"! !TestCase subclass: #AlgoPedidosTestsMios	instanceVariableNames: ''	classVariableNames: ''	package: 'TP1-Tests'!!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:25'!test19QuieroAgregarCuponPorcentualAPedidoInexistente
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarProductoConNombre: 'Ramen' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarCuponAPedidoDe: 'Kirby' conPorcentaje: 10.] raise: PedidoNoEstaError.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:17'!test12PonerYSacarElCuponPorcentual	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conPorcentaje: 10. 		algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Mateo'. 		algoPedidos removerCuponDePedidoDe: 'Mateo'.	self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: 350.0 precision: 0.01.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:22'!test15SacoYPongoCuponEnUnPedidoConMenuYElPrecioQuedaBien	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.	algoPedidos agregarMenuConNombre: 'Menu viernes' precio: 200.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conValor: 10. 			algoPedidos removerMenuConNombre: 'Menu viernes' para: 'Mateo'.	self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: 340.0. "Se aplica descuento"! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:27'!test22RemoverProductoAPedidoInexistente	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoConDeliveryPara: 'Fox'.		algoPedidos agregarProductoConNombre: 'Asado' precio: 500.0 yCantidad: 1 para: 'Fox'.	algoPedidos agregarProductoConNombre: 'vino' precio: 250.0 yCantidad: 1 para: 'Fox'.		self should: [algoPedidos removerProductoConNombre: 'Asado' para: 'Falco'.] raise: PedidoNoEstaError.		! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:19'!test13PongoCuponPongoProductoSacoCuponPongoOtroProductoPongoCuponYElPrecioDaBien	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conValor: 15. 		algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Mateo'.		algoPedidos removerCuponDePedidoDe: 'Mateo'.		algoPedidos agregarProductoConNombre: 'Queso' precio: 100.0 yCantidad: 1 para: 'Mateo'.		algoPedidos agregarCuponAPedidoDe: 'Mateo' conValor: 15. 		self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: 435.0 precision: 0.01. 	! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:28'!test26RemoverMenuInexistente	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoConDeliveryPara: 'Fox'.		algoPedidos agregarMenuConNombre: 'Menu Martes' precio: 500.0 yCantidad: 1 para: 'Fox'.		self should: [algoPedidos removerMenuConNombre: 'Menu Jueves' para: 'Fox'.] raise: ItemNoEstaError .! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:12'!test02SeAgreganProductosAPedidoParaRetirar
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.
	
	algoPedidos agregarProductoConNombre: 'Coca' precio: 1000.0 yCantidad: 1 para: 'Mateo'.
	algoPedidos agregarProductoConNombre: 'Sprite' precio: 1500.0 yCantidad: 1 para: 'Mateo'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Mateo') equals: 2500.0.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:12'!test05AplicarCuponDeDescuentoPorcentualAPedidoConProductosSinDelivery	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.		algoPedidos agregarProductoConNombre: 'Chocotorta' precio: 1000.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conPorcentaje: 15. 		self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: (1000*0.85) precision: 0.01. ! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:25'!test20RemoverCuponDeDescuentoAPedidoInexistente
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Fox'.

	algoPedidos agregarCuponAPedidoDe: 'Fox' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Fox'.
	
	self should: [algoPedidos removerCuponDePedidoDe: 'Falco'.] raise: PedidoNoEstaError.
	

	! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:28'!test25SeCambiaCantidadDeMenuInexistente	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Pit'.		algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Pit'.		self should: [algoPedidos actualizarProductoConNombre: 'Pollo' conCantidad: 3 para: 'Pit'.] raise: ItemNoEstaError .		! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:28'!test27RemoverProductoInexistente	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoConDeliveryPara: 'Fox'.		algoPedidos agregarProductoConNombre: 'Comida Generica' precio: 500.0 yCantidad: 1 para: 'Fox'.		self should: [algoPedidos removerMenuConNombre: 'Comida No Generica' para: 'Fox'.] raise: ItemNoEstaError .! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:13'!test07NoSeCambiaCantidadDeProductos	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.		algoPedidos agregarMenuConNombre: 'Menu Viernes' precio: 200.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarProductoConNombre: 'Ketchup' precio: 10 yCantidad: 2 para: 'Mateo'.		self assert: (algoPedidos cantidadProductosEnPedidoDe: 'Mateo') equals: 3.	! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:21'!test14PongoCuponPongoProductoSacoCuponPongoOtroProductoPongoCuponYElPrecioDaBienPorcentual	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conPorcentaje: 10. 		algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Mateo'.			algoPedidos removerCuponDePedidoDe: 'Mateo'.		algoPedidos agregarProductoConNombre: 'Queso' precio: 100.0 yCantidad: 1 para: 'Mateo'.		algoPedidos agregarCuponAPedidoDe: 'Mateo' conPorcentaje: 10. 		self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: 450.0*0.9 precision: 0.01. ! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:25'!test18QuieroAgregarCuponFijoAPedidoInexistente
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarProductoConNombre: 'Ramen' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarCuponAPedidoDe: 'Kirby' conValor: 10.] raise: PedidoNoEstaError.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:24'!test17QuieroAgregarMenuAPedidoInexistente
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarMenuConNombre: 'Menu Lunes' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarMenuConNombre: 'Menu Viernes' precio: 100.0 yCantidad: 1 para: 'Kirby'.] raise: PedidoNoEstaError.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:27'!test21SeCambiaCantidadDeProductosEnPedidoInexistente	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Fox'.		algoPedidos agregarMenuConNombre: 'Menu viernes' precio: 200.0 yCantidad: 1 para: 'Fox'.	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Fox'.		self should: [algoPedidos actualizarProductoConNombre: 'Gaseosa' conCantidad: 3 para: 'Falco'.] raise: PedidoNoEstaError.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:28'!test24SeCambiaCantidadDeProductoInexistente	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Pit'.		algoPedidos agregarMenuConNombre: 'Menu viernes' precio: 200.0 yCantidad: 1 para: 'Pit'.	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Pit'.		self should: [algoPedidos actualizarProductoConNombre: 'Pollo' conCantidad: 3 para: 'Pit'.] raise: ItemNoEstaError .				! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:28'!test23RemoverMenuAPedidoInexistente	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoConDeliveryPara: 'Fox'.		algoPedidos agregarMenuConNombre: 'Menu Martes' precio: 500.0 yCantidad: 1 para: 'Fox'.		self should: [algoPedidos removerMenuConNombre: 'Menu Martes' para: 'Falco'.] raise: PedidoNoEstaError.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:13'!test08SeCambiaCantidadDeProductosEnPedidoMuchasVeces"Cliente Indeciso"	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.		algoPedidos agregarMenuConNombre: 'Menu Viernes' precio: 200.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarProductoConNombre: 'Ketchup' precio: 10 yCantidad: 2 para: 'Mateo'.			algoPedidos actualizarProductoConNombre: 'Ketchup' conCantidad: 1 para: 'Mateo'.		self assert: (algoPedidos cantidadProductosEnPedidoDe: 'Mateo') equals: 2.	! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:13'!test09SeCambiaCantidadDeProductosEnPedidoYCambiaElPrecio	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.		algoPedidos agregarProductoConNombre: 'acelga' precio: 250.0 yCantidad: 1 para: 'Mateo'.		algoPedidos actualizarProductoConNombre: 'acelga' conCantidad: 3 para: 'Mateo'.		self assert: (algoPedidos  precioPedidoDe: 'Mateo') equals: 750.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:12'!test06AplicarCuponDeDescuentoFijoAPedidoConProductosSinDelivery	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.		algoPedidos agregarProductoConNombre: 'Chocotorta' precio: 1000.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conValor: 15. 		self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: (1000-15) precision: 0.01. ! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:12'!test04AplicarCuponDeDescuentoFijoAPedidoConProductosYDelivery	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoConDeliveryPara: 'Mateo'.		algoPedidos agregarProductoConNombre: 'Chocotorta' precio: 1000.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conValor: 15. 		self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: ((1000-15)*1.2) precision: 0.01. ! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:16'!test11PonerYSacarElCuponFijo	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conValor: 15. 		algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Mateo'. 		algoPedidos removerCuponDePedidoDe: 'Mateo'.	self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: 350.0 precision: 0.01.	! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:11'!test01SeAgreganProductosAPedidoParaRetirar
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.
	
	algoPedidos agregarProductoConNombre: 'Coca' precio: 1000.0 yCantidad: 1 para: 'Mateo'.
	algoPedidos agregarProductoConNombre: 'Sprite' precio: 1500.0 yCantidad: 1 para: 'Mateo'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Mateo') equals: 2500.0.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:12'!test03AplicarCuponDeDescuentoPorcentualAPedidoConProductosYDelivery	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoConDeliveryPara: 'Mateo'.		algoPedidos agregarProductoConNombre: 'Chocotorta' precio: 1000.0 yCantidad: 1 para: 'Mateo'.	algoPedidos agregarCuponAPedidoDe: 'Mateo' conPorcentaje: 15. 		self assert: (algoPedidos precioPedidoDe: 'Mateo') closeTo: ((1000*0.85)*1.2) precision: 0.01. ! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:11'!test10AgregarCuponPorcentualAPedidoConMenuNoRealizaDescuento
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Julian'.

	algoPedidos agregarMenuConNombre: 'Menu jueves' precio: 200.0 yCantidad: 1 para: 'Julian'.

	algoPedidos agregarCuponAPedidoDe: 'Julian' conPorcentaje: 15.
	
	self assert: (algoPedidos precioPedidoDe: 'Julian') equals: 200.0.! !!AlgoPedidosTestsMios methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:51'!test16QuieroAgregarProductoAPedidoInexistente
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarProductoConNombre: 'Ramen' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarProductoConNombre: 'Gelatina' precio: 100.0 yCantidad: 1 para: 'Kirby'.] raise: PedidoNoEstaError.! !TestCase subclass: #AumentoEnvioTests	instanceVariableNames: ''	classVariableNames: ''	package: 'TP1-Tests'!!AumentoEnvioTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 16:03'!test03NoAceptaPreciosNegativos	|aumento|	aumento := AumentoEnvio new.	self should: [aumento aumentarPrecio: -100] raise: ValorInvalidoError .! !!AumentoEnvioTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:57'!test01SeAumentaBienElPrecio	|aumento|	aumento := AumentoEnvio new.	aumento activarEnvio.	self assert: (aumento aumentarPrecio: 100) equals: 120.! !!AumentoEnvioTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 16:03'!test02SiNoSeActivaNoAumenta	|aumento|	aumento := AumentoEnvio new.	self assert: (aumento aumentarPrecio: 100) equals: 100.! !TestCase subclass: #CuponTests	instanceVariableNames: ''	classVariableNames: ''	package: 'TP1-Tests'!!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:04'!test09CambiaElTipoDeCuponDePorcentualAFijo
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Martin'.
	algoPedidos agregarCuponAPedidoDe: 'Martin' conPorcentaje: 10.

	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 200 yCantidad: 1 para: 'Martin'.
	algoPedidos agregarCuponAPedidoDe: 'Martin' conValor: 10. 	
	
	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 190 precision: 0.01.! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:02'!test08CambiaElTipoDeCuponDeFijoAPorcentual
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Martin'.

	algoPedidos agregarCuponAPedidoDe: 'Martin' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 200 yCantidad: 1 para: 'Martin'.
	
	algoPedidos agregarCuponAPedidoDe: 'Martin' conPorcentaje: 10.

	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 180 precision: 0.01.! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 14:48'!test02AplicarCuponDeDescuentoPorcentualMenorACeroAPedidoConProductos	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Ash'.		algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 1 para: 'Ash'.	self should: [algoPedidos  agregarCuponAPedidoDe: 'Ash' conPorcentaje: (-10).] raise: ValorInvalidoError.		! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 14:49'!test06PrueboElFuncionamientoDelCuponFijo	|cupon|	cupon := CuponFijo conValor: 10.	self assert: (cupon aplicarDescuento: 100) equals: 90.! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 14:52'!test07PrueboElFuncionamientoDelCuponNulo	|cupon|	cupon := CuponNulo new.	self assert: (cupon aplicarDescuento: 100) equals: 100.! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 14:35'!test01AplicarCuponDeDescuentoPorcentualMayorACienAPedidoConProductos	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Ash'.		algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 1 para: 'Ash'.	self should: [algoPedidos agregarCuponAPedidoDe: 'Ash' conPorcentaje: 102.] raise: ValorInvalidoError.		! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 14:36'!test03AplicarCuponDeDescuentoFijoMenorACeroAPedidoConProductos	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Ash'.		algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 1 para: 'Ash'.	self should: [algoPedidos agregarCuponAPedidoDe: 'Ash' conValor: -10.] raise: ValorInvalidoError.! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 14:47'!test05PrueboElFuncionamientoDelCuponPorcentual	|cupon|	cupon := CuponPorcentual conPorcentaje: 10.	self assert: (cupon aplicarDescuento: 100) equals: 90.! !!CuponTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 14:36'!test04AplicarCuponDeDescuentoFijoMayoAlValorTotalAPedidoConProductos	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Ash'.		algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 1 para: 'Ash'.	algoPedidos agregarCuponAPedidoDe: 'Ash' conValor: 500.	self assert: (algoPedidos precioPedidoDe: 'Ash') equals: 0.! !TestCase subclass: #ItemTests	instanceVariableNames: ''	classVariableNames: ''	package: 'TP1-Tests'!!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:15'!test10SeAsignaBienLaCantidadDeMenu	|menu|	menu := Menu new.	menu asignarPrecio: 50 YCantidad: 1.	self assert: (menu tenerCantidad ) equals: 1.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:15'!test09SeCambiaLaCantidadDeProducto	|producto|	producto := Producto new.	producto asignarPrecio: 50 YCantidad: 1.	producto cambiarCantidad: 2.	self assert: (producto tenerCantidad ) equals: 2.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:16'!test11SeAsignanBienElNombreDeMenu	|menu|	menu := Menu new.	menu asignarNombre: 'Menu Falco'.	self assert: (menu obtenerNombre) equals: 'Menu Falco'.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:17'!test12SeCalculaElPrecioTotalDelMenu	|menu|	menu := Menu new.	menu asignarPrecio: 50 YCantidad: 3.	self assert: (menu Precio ) equals: 150.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:17'!test13SeCambiaLaCantidadDeProductoMenu	|menu|	menu := Menu new.	menu asignarPrecio: 50 YCantidad: 1.	menu cambiarCantidad: 2.	self assert: (menu tenerCantidad ) equals: 2.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:58'!test04SeAgregaProductoConPrecioNegativo
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mario'.
	
	self should: [algoPedidos agregarMenuConNombre: 'Menu generico' precio: -250.0 yCantidad: 1 para: 'Mario'.] raise: ValorInvalidoError.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:13'!test08SeCalculaElPrecioTotalDelProducto	|producto|	producto := Producto new.	producto asignarPrecio: 50 YCantidad: 3.	self assert: (producto Precio ) equals: 150.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:58'!test02SeCambiaCantidadDeProductosEnPedidoAUnaNegativa	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Luigi'.		algoPedidos agregarMenuConNombre: 'Menu viernes' precio: 200.0 yCantidad: 1 para: 'Luigi'.	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Luigi'.		self should: [algoPedidos actualizarProductoConNombre: 'Gaseosa' conCantidad: -1 para: 'Luigi'.] raise: ValorInvalidoError.			! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:57'!test01SeAgreganProductosConCantidadNegativa
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mario'.
	
	self should: [algoPedidos agregarProductoConNombre: 'Milanesa' precio: 250.0 yCantidad: -1 para: 'Mario'.] raise: ValorInvalidoError.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:09'!test06SeAsignanBienElNombreDeProducto	|producto|	producto := Producto new.	producto asignarNombre: 'Milanesa'.	self assert: (producto obtenerNombre) equals: 'Milanesa'.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:58'!test05SeAgregaMenuConPrecioNegativo
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mario'.
	
	self should: [algoPedidos agregarMenuConNombre: 'Menu generico' precio: -250.0 yCantidad: 1 para: 'Mario'.] raise: ValorInvalidoError.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:12'!test07SeAsignanBienLaCantidadDeProducto	|producto|	producto := Producto new.	producto asignarPrecio: 50 YCantidad: 1.	self assert: (producto tenerCantidad ) equals: 1.! !!ItemTests methodsFor: 'tests' stamp: 'Mateo 12/7/2020 16:58'!test03SeCambiaCantidadDeMenuEnPedidoAUnaNegativa	| algoPedidos | 		algoPedidos := AlgoPedidos new.	algoPedidos crearPedidoParaRetirarPara: 'Luigi'.		algoPedidos agregarMenuConNombre: 'Menu viernes' precio: 200.0 yCantidad: 1 para: 'Luigi'.	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Luigi'.		self should: [algoPedidos actualizarProductoConNombre: 'Menu viernes' conCantidad: -1 para: 'Luigi'.] raise: ValorInvalidoError.			! !TestCase subclass: #PedidoTests	instanceVariableNames: ''	classVariableNames: ''	package: 'TP1-Tests'!!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:46'!test09SeEliminaUnItem	|pedido producto otroProducto|	pedido := Pedido new.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	otroProducto:= Producto conNombre: 'Queso' precio: 30 yCantidad: 1.	pedido agregar: 3 de: producto.	pedido agregar: 1 de: otroProducto.	pedido eliminarItem: 'Queso'.	self assert: (pedido obtenerPrecio) equals: 150.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:29'!test01SeCalculaElPrecioTotal 	|pedido producto|	pedido := Pedido new.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	self assert: (pedido obtenerPrecio) equals: 150.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:49'!test10SeActualizaLaCantidad	|pedido producto|	pedido := Pedido new.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	pedido actualizarCantidadDe: 'Milanesa' A: 4. 	self assert: (pedido obtenerCantidad) equals: 4.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:48'!test11SeEliminaUnItemQueNoEsta	|pedido producto otroProducto|	pedido := Pedido new.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	otroProducto:= Producto conNombre: 'Queso' precio: 30 yCantidad: 1.	pedido agregar: 3 de: producto.	pedido agregar: 1 de: otroProducto.		self should: [pedido eliminarItem: 'Maracuya'] raise: ItemNoEstaError .! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:37'!test07SeEliminaCuponFijo	|pedido producto cupon|	cupon := CuponFijo  conValor: 10.	pedido := Pedido new.	pedido usarCupon: cupon.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	pedido eliminarCupon.	self assert: (pedido obtenerPrecio) equals: 150.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:29'!test02SeCalculaLaCantidad	|pedido producto|	pedido := Pedido new.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	self assert: (pedido obtenerCantidad) equals: 3.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:34'!test05SeCalculaElPrecioTotalConCuponPorcentual	|pedido producto cupon|	cupon := CuponPorcentual  conPorcentaje: 10.	pedido := Pedido new.	pedido usarCupon: cupon.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	self assert: (pedido obtenerPrecio) equals: 135.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:33'!test04SeCalculaElPrecioTotalConCuponFijo	|pedido producto cupon|	cupon := CuponFijo conValor: 10.	pedido := Pedido new.	pedido usarCupon: cupon.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	self assert: (pedido obtenerPrecio) equals: 140.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:37'!test06SeEliminaCuponPorcentual	|pedido producto cupon|	cupon := CuponPorcentual  conPorcentaje: 10.	pedido := Pedido new.	pedido usarCupon: cupon.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	pedido eliminarCupon.	self assert: (pedido obtenerPrecio) equals: 150.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:31'!test03SeCalculaElPrecioTotalConEnvioActivado	|pedido producto|	pedido := Pedido new.	pedido activarEnvio.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	self assert: (pedido obtenerPrecio) equals: 180.! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:50'!test12SeActualizaLaCantidadDeUnItemQueNoEsta	|pedido producto|	pedido := Pedido new.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	pedido agregar: 3 de: producto.	 	self should: [pedido actualizarCantidadDe: 'Yerba' A: 4] raise: ItemNoEstaError .! !!PedidoTests methodsFor: 'tests' stamp: 'Mateo 12/8/2020 15:41'!test08SeCalculaElPrecioTotalConMasDeUnProducto	|pedido producto otroProducto|	pedido := Pedido new.	producto:= Producto conNombre: 'Milanesa' precio: 50 yCantidad: 3.	otroProducto:= Producto conNombre: 'Queso' precio: 30 yCantidad: 1.	pedido agregar: 3 de: producto.	pedido agregar: 1 de: otroProducto.	self assert: (pedido obtenerPrecio) equals: 180.! !