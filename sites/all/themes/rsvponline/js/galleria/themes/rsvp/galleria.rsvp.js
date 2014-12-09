(function($) {
  Galleria.addTheme({
    name: "rsvp",
    author: "RSVP",
    css: "galleria.rsvp.css",
    defaults: {
      transition: "fade",
      transitionSpeed: 500,
      imageCrop: false,
      thumbCrop: "height",
      idleMode: "hover",
      idleSpeed: 500,
      fullscreenTransition: false,
      _locale: {
        show_captions: "Mostrar descripción",
        hide_captions: "Ocultar descripción",
        play: "Reproducir",
        pause: "Pausar",
        enter_fullscreen: "Pantalla completa",
        exit_fullscreen: "Salir de pantalla completa",
        next: "Siguiente",
        prev: "Anterior",
        showing_image: "Mostrar un %s de la imagen de un total de %s"
      },
      _toggleInfo: true,
      _toggleCaption: true,
      _showCaption: true,
      _showTooltip: true
    },
    init: function(options) {
      Galleria.requires(1.28, "Esta versión del tema de RSVP necesita Galleria versión 1.2.8 o posterior");
      this.addElement("bar", "fullscreen", "play").append({
        container: "bar",
        bar: ["fullscreen", "play", "thumbnails-container"]
      }).prependChild("stage", "info").appendChild("container", "tooltip");
      var gallery = this,
          document = window.document,
          lang = options._locale;
      var infoState = Galleria.IE < 9 ? {
        bottom: -100
      } : {
        bottom: -50,
        opacity: 0
      },
      counterState = Galleria.IE < 9 ? {
        top: -20
      } : {
        opacity: 0,
        top: -20
      };
      this.bind("play", function() {
        this.$("play").addClass("pause");
      }).bind("pause", function() {
        this.$("play").removeClass("pause");
      }).bind("loadstart", function(e) {
        if (!e.cached) {
            this.$("loader").show()
        }
      }).bind("loadfinish", function(e) {
         this.$("loader").hide()
      });
      this.addIdleState(this.get("info"), infoState, Galleria.IE < 9 ? {} : {
        opacity: 1
      }, true).addIdleState(this.get("image-nav-left"), {
        opacity: 0,
        left: 0
      }, {
        opacity: 1
      }, true).addIdleState(this.get("image-nav-right"), {
        opacity: 0,
        right: 0
      }, {
        opacity: 1
      }, true).addIdleState(this.get("counter"), counterState, Galleria.IE < 9 ? {} : {
        opacity: .9
      }, true);
      this.$("fullscreen").click(function(e) {
        e.preventDefault();
        gallery.toggleFullscreen()
      });
      this.$("play").click(function(e) {
        e.preventDefault();
        gallery.playToggle()
      });
      if (options._toggleCaption) {
        this.$("info").addClass("toggler");
        this.addElement("captionopen").appendChild("stage", "captionopen");
        this.addElement("captionclose").appendChild("info", "captionclose");
        this.$("captionopen").click(function() {
          gallery.$("info").addClass("open");
          $(this).hide()
        }).html(lang.show_captions);
        this.bind("loadstart", function() {
          this.$("captionopen").toggle(!gallery.$("info").hasClass("open") && this.hasInfo())
        });
        this.$("captionclose").click(function() {
          gallery.$("info").removeClass("open");
          if (gallery.hasInfo()) {
            gallery.$("captionopen").show()
          }
        }).html("&#215;");
        if (options._showCaption) {
          this.$("captionopen").click()
        }
      }
      if (options._showTooltip) {
        this.bindTooltip({
          fullscreen: function() {
            return gallery.isFullscreen() ? lang.exit_fullscreen : lang.enter_fullscreen
          },
          play: function() {
            return gallery.isPlaying() ? lang.pause : lang.play
          },
          captionclose: lang.hide_captions,
          "image-nav-right": lang.next,
          "image-nav-left": lang.prev,
          counter: function() {
            return lang.showing_image.replace(/\%s/, gallery.getIndex() + 1).replace(/\%s/, gallery.getDataLength())
          }
        })
      }
    }
  })
})(jQuery);
