var Module = {
					print: function () {
						var e = document.getElementById("output");
						return e && (e.value = ""),
							function (n) {
								arguments.length > 1 && (n = Array.prototype.slice.call(arguments).join(" ")),
									console.log(n),
									e && (e.value += n + "\n", e.scrollTop = e.scrollHeight);
							}
					}(),
					canvas: document.getElementById("canvas")
				};

				// Fullscreen toggle functionality
				document.getElementById('fullscreen-toggle').addEventListener('change', function () {
					var canvas = document.getElementById('canvas');
					if (this.checked) {
						// Only make the canvas fullscreen
						if (canvas.requestFullscreen) {
							canvas.requestFullscreen();
						} else if (canvas.mozRequestFullScreen) {
							canvas.mozRequestFullScreen();
						} else if (canvas.webkitRequestFullscreen) {
							canvas.webkitRequestFullscreen();
						} else if (canvas.msRequestFullscreen) {
							canvas.msRequestFullscreen();
						}
					} else {
						// Exit fullscreen only if canvas is in fullscreen
						if (
							document.fullscreenElement === canvas ||
							document.mozFullScreenElement === canvas ||
							document.webkitFullscreenElement === canvas ||
							document.msFullscreenElement === canvas
						) {
							if (document.exitFullscreen) {
								document.exitFullscreen();
							} else if (document.mozCancelFullScreen) {
								document.mozCancelFullScreen();
							} else if (document.webkitExitFullscreen) {
								document.webkitExitFullscreen();
							} else if (document.msExitFullscreen) {
								document.msExitFullscreen();
							}
						}
					}
				});

				// Handle fullscreen change events
				const fullscreenEvents = [
					'fullscreenchange',
					'mozfullscreenchange',
					'webkitfullscreenchange',
					'msfullscreenchange'
				];

				fullscreenEvents.forEach(event => {
					document.addEventListener(event, () => {
						const checkbox = document.getElementById('fullscreen-toggle');
						const canvas = document.getElementById('canvas');
						checkbox.checked = !!(
							document.fullscreenElement === canvas ||
							document.mozFullScreenElement === canvas ||
							document.webkitFullscreenElement === canvas ||
							document.msFullscreenElement === canvas
						);
					});
				});