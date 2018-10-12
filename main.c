#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define WLR_USE_UNSTABLE
#include <wayland-client.h>
#include "idle-inhibit-unstable-v1.h"

void cleanup (int sig) {
  // no-op. just silently handle signal so pause() works
}

static struct wl_compositor *compositor = NULL;
static struct zwp_idle_inhibit_manager_v1 *manager = NULL;
static struct zwp_idle_inhibitor_v1 *inhibitor = NULL;


static void handle_global(void *data, struct wl_registry *registry,
    uint32_t name, const char *interface, uint32_t version) {
  if (strcmp(interface, "wl_compositor") == 0) {
    compositor = wl_registry_bind(registry, name,
      &wl_compositor_interface, 1);
  } else if (strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
    manager = wl_registry_bind(registry, name, &zwp_idle_inhibit_manager_v1_interface, 1);
  }
}

static void handle_global_remove(void *data, struct wl_registry *registry,
    uint32_t name) {
  // who cares
}

static const struct wl_registry_listener registry_listener = {
  .global = handle_global,
  .global_remove = handle_global_remove,
};


int main () {
  printf("Inhibiting idle...\n");
  struct wl_display *display = wl_display_connect(NULL);
  assert(display);

  struct wl_registry *registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, NULL);
  wl_display_dispatch(display);
  wl_display_roundtrip(display);

  struct wl_surface *surface = wl_compositor_create_surface(compositor);
  assert(surface);

  assert(manager);
  inhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(manager, surface);
  printf("Idle inhibited.\n");
  // Wait until a quit signal before cleaning up
  signal(SIGINT, cleanup);
  pause();

  printf("Uninhibiting idle...\n");
  zwp_idle_inhibitor_v1_destroy(inhibitor);
  printf("Done.\n");
  return 0;
}
