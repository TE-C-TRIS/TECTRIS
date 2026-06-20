#!/usr/bin/env python3
"""
Gerador de audio original para o Tectris (musica + efeitos sonoros).
Nao reproduz nenhuma trilha existente (ex: tema classico do Tetris) -
toda a composicao e original, sintetizada por osciladores simples
(quadrada/triangular/dente-de-serra), no estilo 8-bit/chiptune.

Gera arquivos .wav PCM 16-bit mono em assets/audio/.
Sem dependencias externas (so usa a stdlib do Python).
"""
import wave
import struct
import math
import os
import random

SR = 44100  # sample rate

def square(freq, t):
    return 1.0 if math.sin(2*math.pi*freq*t) >= 0 else -1.0

def triangle(freq, t):
    return 2.0*abs(2.0*((t*freq) % 1.0) - 1.0) - 1.0

def sine(freq, t):
    return math.sin(2*math.pi*freq*t)

def sawtooth(freq, t):
    return 2.0*((t*freq) % 1.0) - 1.0

WAVEFORMS = {'square': square, 'triangle': triangle, 'sine': sine, 'saw': sawtooth}

def envelope(t, dur, attack=0.008, release=0.04):
    """Envelope linear simples para evitar cliques (attack/release)."""
    if t < attack:
        return t/attack
    if t > dur - release:
        return max(0.0, (dur - t)/release)
    return 1.0

def render_note(freq, dur, wave_name='square', vol=0.5, pitch_slide=0.0):
    """Renderiza uma nota/tom isolado. pitch_slide: variacao total de freq ao longo da nota (Hz)."""
    fn = WAVEFORMS[wave_name]
    n = int(SR*dur)
    samples = []
    for i in range(n):
        t = i/SR
        f = freq + pitch_slide*(t/dur)
        s = fn(f, t) * vol * envelope(t, dur)
        samples.append(s)
    return samples

def mix(*tracks):
    """Mistura varias listas de samples (preenchendo com silencio as mais curtas)."""
    length = max(len(t) for t in tracks)
    out = [0.0]*length
    for t in tracks:
        for i, s in enumerate(t):
            out[i] += s
    # normaliza suavemente se passar de 1.0
    peak = max((abs(s) for s in out), default=1.0)
    if peak > 1.0:
        out = [s/peak*0.97 for s in out]
    return out

def concat_notes(note_list, wave_name='square', vol=0.5):
    """note_list: lista de (freq_or_None, duracao_em_segundos)."""
    out = []
    for freq, dur in note_list:
        if freq is None or freq == 0:
            out.extend([0.0]*int(SR*dur))
        else:
            out.extend(render_note(freq, dur, wave_name=wave_name, vol=vol))
    return out

def save_wav(path, samples):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with wave.open(path, 'w') as f:
        f.setnchannels(1)
        f.setsampwidth(2)
        f.setframerate(SR)
        frames = bytearray()
        for s in samples:
            v = int(max(-1.0, min(1.0, s)) * 32767)
            frames += struct.pack('<h', v)
        f.writeframes(bytes(frames))
    print(f'  -> {path}  ({len(samples)/SR:.2f}s)')

OUT = 'assets/audio'

# ---------------------------------------------------------------
# MUSICA DE FUNDO (composicao original, NAO e o tema classico do Tetris)
# Melodia em La menor, andamento ~140bpm, lead quadrada + baixo triangular
# ---------------------------------------------------------------
def note(name, octave):
    NOTES = {'C':-9,'C#':-8,'D':-7,'D#':-6,'E':-5,'F':-4,'F#':-3,'G':-2,'G#':-1,'A':0,'A#':1,'B':2}
    n = NOTES[name] + (octave-4)*12
    return 440.0 * (2 ** (n/12.0))

def gen_music():
    print('Gerando musica de fundo original...')
    beat = 60.0/140.0  # semina a 140bpm
    e = beat/2  # colcheia

    melody_steps = [
        ('A',4,1),('C',5,1),('E',5,1),('A',5,1),
        ('G',5,1),('E',5,1),('C',5,1),('A',4,1),
        ('F',4,1),('A',4,1),('C',5,1),('F',5,1),
        ('E',5,1),('C',5,1),('A',4,1),(None,0,1),
        ('A',4,1),('C',5,1),('E',5,1),('A',5,1),
        ('B',5,1),('A',5,1),('G',5,1),('E',5,1),
        ('D',5,1),('C',5,1),('B',4,1),('A',4,2),
    ]
    bass_steps = [
        ('A',2,4),('F',2,4),
        ('G',2,4),('E',2,4),
        ('A',2,4),('F',2,4),
        ('G',2,2),('E',2,2),
    ]

    mel_notes = []
    for n_, oct_, dur in melody_steps:
        f = None if n_ is None else note(n_, oct_)
        mel_notes.append((f, dur*e))
    bass_notes = []
    for n_, oct_, dur in bass_steps:
        f = note(n_, oct_)
        bass_notes.append((f, dur*e))

    lead = concat_notes(mel_notes, wave_name='square', vol=0.34)
    bass = concat_notes(bass_notes, wave_name='triangle', vol=0.30)
    # leve percussao sintetica (ruido curto) a cada beat para dar groove
    perc = []
    total_beats = sum(d for _, _, d in melody_steps)
    for i in range(int(total_beats)):
        if i % 2 == 1:
            n = int(SR*0.045)
            for k in range(n):
                t = k/SR
                v = random.uniform(-1,1) * envelope(t, 0.045, attack=0.001, release=0.04) * 0.12
                perc.append(v)
            perc.extend([0.0]*int(SR*(beat-0.045)))
        else:
            perc.extend([0.0]*int(SR*beat))

    full = mix(lead, bass, perc)
    save_wav(f'{OUT}/music_loop.wav', full)

# ---------------------------------------------------------------
# EFEITOS SONOROS
# ---------------------------------------------------------------
def gen_sfx():
    print('Gerando efeitos sonoros...')

    # Resposta correta: arpejo ascendente alegre
    correct = concat_notes([
        (note('C',5), 0.08), (note('E',5), 0.08), (note('G',5), 0.08), (note('C',6), 0.16)
    ], wave_name='square', vol=0.5)
    save_wav(f'{OUT}/sfx_correct.wav', correct)

    # Resposta errada: zumbido descendente
    wrong = render_note(220, 0.30, wave_name='saw', vol=0.45, pitch_slide=-90)
    save_wav(f'{OUT}/sfx_wrong.wav', wrong)

    # Peca encaixando (lock)
    lock = render_note(140, 0.06, wave_name='square', vol=0.35)
    save_wav(f'{OUT}/sfx_lock.wav', lock)

    # Linha completada (line clear): sweep ascendente
    lineclear = concat_notes([
        (note('A',4), 0.06), (note('C',5), 0.06), (note('E',5), 0.06), (note('A',5), 0.12)
    ], wave_name='square', vol=0.45)
    save_wav(f'{OUT}/sfx_lineclear.wav', lineclear)

    # Linha de penalidade adicionada / ataque ao adversario: thud grave
    penalty = render_note(90, 0.22, wave_name='triangle', vol=0.5, pitch_slide=-20)
    save_wav(f'{OUT}/sfx_penalty.wav', penalty)

    # Kill Line subindo (aviso de perigo)
    warning = concat_notes([
        (note('F',5), 0.07), (None, 0.04), (note('F',5), 0.07)
    ], wave_name='square', vol=0.4)
    save_wav(f'{OUT}/sfx_warning.wav', warning)

    # Game Over: descida triste
    gameover = concat_notes([
        (note('E',4), 0.18), (note('C',4), 0.18), (note('A',3), 0.36)
    ], wave_name='triangle', vol=0.45)
    save_wav(f'{OUT}/sfx_gameover.wav', gameover)

    # Vitoria: fanfarra curta (duas triades ascendentes)
    win = concat_notes([
        (note('C',5), 0.1), (note('E',5), 0.1), (note('G',5), 0.18), (None, 0.03),
        (note('C',5), 0.1), (note('E',5), 0.1), (note('G',5), 0.1), (note('C',6), 0.26),
    ], wave_name='square', vol=0.5)
    save_wav(f'{OUT}/sfx_win.wav', win)

    # Navegacao no menu: blip curto
    select = render_note(660, 0.045, wave_name='square', vol=0.3)
    save_wav(f'{OUT}/sfx_select.wav', select)

    # Caixa de resposta aberta (multiplayer): blip de confirmacao
    open_input = concat_notes([
        (note('A',4), 0.05), (note('C',5), 0.07)
    ], wave_name='square', vol=0.35)
    save_wav(f'{OUT}/sfx_open_input.wav', open_input)

if __name__ == '__main__':
    random.seed(42)
    gen_music()
    gen_sfx()
    print('Concluido.')
